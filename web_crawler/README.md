# Crawler
Crawler takes a file with newline separated companies names and generates file with metadata for each company using yandex xml search.

File for "YANDEX" query looks like:

    <?xml version="1.0" encoding="utf-8"?>

    <yandexsearch version="1.0"><request><query>YANDEX</query> ..... </yandexsearch>

# XML parser
Parses file from crawler and generates output.csv:

    company_name, metadata
    NAME,JSON

example:

    company_name,metadata

    YANDEX,"{""docs"": [{""title"": ""Яндекс — поисковая система и интернет-портал"", ""headline"": ""Поиск по интернету с учётом региона пользователя."}]}"
