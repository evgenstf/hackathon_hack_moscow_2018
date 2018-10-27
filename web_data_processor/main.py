import argparse
import json
import numpy as np
import pandas as pd
import re

from sklearn.feature_extraction import text


def merge_docs(docs):
    result = []
    for doc in docs:
        for key in ('title', 'headline'):
            if key in doc:
                result.append(doc[key])
    return ' '.join(result)


def process_metadata(metadata):
    result = pd.DataFrame()

    metadata = metadata.apply(
        lambda x: json.loads(x)
    )

    result['docs'] = metadata.apply(
        lambda x: x['docs'] if 'docs' in x else []
    )

    result['merged_text'] = result['docs'].apply(merge_docs)
    result.drop('docs', inplace=True, axis=1)

    result['merged_text'] = result['merged_text'].apply(str.lower)
    return result


def main(args):
    df = pd.read_csv(args.input_file, encoding='utf-8')

    features = process_metadata(df['metadata'])

    df.drop('metadata', inplace=True, axis=1)
    df = pd.concat([df, features], axis=1)

    vectorizer = text.CountVectorizer(
        ngram_range=(1, 2),
        max_features=args.max_features
    )

    vectorizer.fit(df['merged_text'])
    features_vector = pd.DataFrame(
        columns=vectorizer.vocabulary_,
        data=vectorizer.transform(df['merged_text']).todense()
    )
    df.drop('merged_text', inplace=True, axis=1)

    df = pd.concat((df, features_vector), axis=1)
    df.to_csv(args.output_file, index=False)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(add_help=True)

    parser.add_argument('--input-file', help='path to file with newline separeted companies names', type=str)
    parser.add_argument('--output-file', help='path to result file', type=str)
    parser.add_argument('--max-features', help='max features for vector counter', type=int, default=10)

    args = parser.parse_args()

    main(args)
