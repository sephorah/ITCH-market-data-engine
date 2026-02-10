# ITCH Market Data Engine

This project is a C++ library that parses ITCH messages sequentially and builds order books, exposed to Python through pybind11 for analysis.

Currently in development.

## Architecture diagram

```mermaid
flowchart TD

    config_file["**Configuration file** with instruments details (ID, symbol, order book depth)"]
    
    nasdaq_itch_file[**NASDAQ TotalView-ITCH 5.0 historical file**<br/>• Replayed as a continuous event stream, providing level 3 market data]

    subgraph cpp_server[**C++ library**]

        itch_parser["**ITCH Parser**<br/>• Decodes ITCH messages and emits normalized order events"]

        order_book_manager[**Order book manager**<br/>• Applies events to maintain order book state<br/>• Manages order books for all instruments]
        
        order_book[**Order book**<br/>• Lists bids and asks for an instrument]

        pybind11_interface[**Pybind11 bindings**<br/>• Exposes C++ API to Python<br/>• Zero-copy data transfer via NumPy arrays]
    end

    subgraph python_layer[**Python Research layer**]

        update_buffers[**Update buffers per instrument**<br/>• Maintains separate buffer per instrument<br/>• Collects updates up to 1000 per instrument]

        polars_processing[**Polars processing**<br/>• Processes each instrument independently<br/>• Triggers when instrument reaches 1000 updates<br/>• Extracts features and saves to Parquet]
    end

    parquet_files[**Parquet files**]
    
    pandas_analysis[**Pandas analysis**<br/>• Jupyter notebooks<br/>• Loads Parquet files for statistical analysis and visualizations]


    config_file -->|Specifies instruments to observe| order_book_manager
    order_book_manager --> order_book
    nasdaq_itch_file --> itch_parser
    itch_parser --> order_book_manager
    order_book_manager --> pybind11_interface
    pybind11_interface --> update_buffers
    update_buffers --> polars_processing
    polars_processing --> parquet_files
    parquet_files --> pandas_analysis
```

## Stack used

- Build system: [CMake](https://cmake.org/), a cross-platform build system generator.
- Package manager: [Conan](https://conan.io/), a C/C++ dependency manager widely used in production environments.

### Librairies

- [cxxopts](https://github.com/jarro2783/cxxopts): a lightweight C++ command line option parser.


## Getting started

### Requirements

The project requires the following to run:

- [CMake](https://cmake.org/): if not installed, refer to the [installation guide](https://cmake.org/download/).
- [Conan](https://conan.io/): if not installed, refer to the [installtion guide](https://docs.conan.io/2/installation.html).

Run the following command:
```sh
conan profile detect --force
```

### Dataset

Download raw ITCH 5.0 data `01302020.NASDAQ_ITCH50.gz` from `https://emi.nasdaq.com/ITCH/Nasdaq%20ITCH/`.

The data format is defined by the document [Nasdaq TotalView-ITCH 5.0](https://www.nasdaqtrader.com/content/technicalsupport/specifications/dataproducts/NQTVITCHspecification.pdf).

### Installation

1. Clone the git repository.
```sh
git clone git@github.com:sephorah/ITCH-market-data-engine.git
cd ITCH-market-data-engine
```

2. Install dependencies.
```sh
./bin/setup.sh install
```

3. Build the project.
```sh
./bin/setup.sh build
```

4. Run the project.

