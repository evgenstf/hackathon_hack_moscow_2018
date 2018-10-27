import argparse
import json
import os
import requests

from const import URL_PATTERN


def crawl(company_name):
    r = requests.get(URL_PATTERN.format(company_name))

    if r.status_code != 200:
        return None

    return r.json


def get_companies_names(path):
    with open(path) as f:
         companies_names = f.read().split('\n')
         return companies_names


def main(args):
    companies_names = get_companies_names(args.companies_file)

    if args.limit is not None:
        companies_names = companies_names[:args.limit]

    result = []
    for company_name in companies_names:
        crawled_data = crawl(company_name)

        if crawled_data is None:
            break

        result.append(crawled_data)

    with open(args.output_file, 'w') as f:
        f.write(args.result_separato.join(result))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(add_help=True)

    parser.add_argument('--companies-file', help='path to file with newline separeted companies names', type=str)
    parser.add_argument('--output-file', help='path to result file', type=str)
    parser.add_argument('--result-separator', default='\n', help='separator for result', type=str)
    parser.add_argument('--limit', default=None, help='limit for crawl', type=int)

    args = parser.parse_args()

    main(args)
