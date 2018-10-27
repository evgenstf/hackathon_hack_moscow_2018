import argparse
import pandas as pd
import json

from lxml import objectify
from lxml import etree


def read_file(path):
    xml_raw = []
    with open(path, encoding='utf-8') as f:
        all_data = f.read().split('\n')
        for i, data  in enumerate(all_data):
            if i % 2 != 0: # skip xml version row
                xml_raw.append(data)
    return xml_raw


def parse(raw):
    try:
        root = objectify.fromstring(raw)

        data = dict()
        data['company_name'] = root.request.query

        metadata = dict()
        for grouping in root.response.results.grouping:
            for group in grouping.group:
                doc = group.doc

                doc_info = dict()

                has_key = lambda element, key: element.find(key) is not None
                get_text_from_element = lambda element, key: ''.join(element.find(key).itertext())

                for key in ('title', 'headline'):
                    if has_key(doc, key):
                        doc_info[key] = get_text_from_element(doc, key)
                props = doc.properties
                if has_key(props, 'Snippet'):
                    doc_info['Snippet'] = get_text_from_element(props, 'Snippet')

                if 'docs' not in metadata:
                    metadata['docs'] = []
                metadata['docs'].append(doc_info)

        data['metadata'] = json.dumps(metadata, ensure_ascii=False)
        return data
    except:
        return None


def main(args):
    xml_raw = read_file(args.input_file)

    xml_parsed = pd.DataFrame(columns=['company_name', 'metadata'])
    for raw in xml_raw:
        parsed_dict = parse(raw)
        if parsed_dict is not None:
            xml_parsed = xml_parsed.append(parse(raw), ignore_index=True)

    xml_parsed.to_csv(args.output_file, index=False, encoding='utf-8')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(add_help=True)

    parser.add_argument('--input-file', help='path to file with newline separeted xml data', type=str)
    parser.add_argument('--output-file', help='path to result file', type=str)

    args = parser.parse_args()

    main(args)
