# It's not a good title
> Program that takes a single column CSV file containing IP's and batch geolocates the addresses, outputting a JSON file with latitude and longitude.

This program inputs a CSV file (ip_list.csv) of IP objects (that I downloaded from Chronograf) that was collected by my honeypot (_[cowrie](https://github.com/micheloosterhof/cowrie)_). From there it reads the CSV data using [fast-csv](https://github.com/C2FO/fast-csv). From there it runs the data through [Fetch](https://www.npmjs.com/package/fetch) calling the [IPstack](https://ipstack.com/) API. The API returns location data for the IP address along with a few other useful data points, in a JSON object. The JSON object is parsed for the latitude and longitude values and written to a file location.json by [jsonfile](https://github.com/jprichardson/node-jsonfile).

## Installation

OS X & Linux:

```sh
npm install fast-csv
npm install fetch
npm install jsonfile
```

## Development setup

Describe how to install all development dependencies and how to run an automated test-suite of some kind. Potentially do this for multiple platforms.

```sh
node read_csv.js (test that fast-csv is functioning) (optional)
node json_write.js (test that jsonfile is functioning) (optional)

node csv_to_json.js (run final file)
```

## Release History

* 0.0.1
    * First release (07.19.18)

## Meta

Michael Peters – michael@michaelpeterswa.com

Distributed under the MIT license. See ``LICENSE`` for more information.

[https://github.com/michaelpeterswa](https://github.com/michaelpeterswa)

## Contributing if you feel like you need to

1. Fork it
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request
