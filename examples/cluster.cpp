// Copyright 2018, Sebastian Achim Mueller
//
// compile using:
// g++ docopt/docopt.cpp cluster.cpp -o phs.cluster -std=gnu++11

#include <stdio.h>
#include <string.h>
#include <array>
#include <fstream>
#include <iostream>
#include "../photon_stream.h"
#include "./density_based_air_shower_photon_classification.h"
#include "docopt/docopt.h"

namespace ps = photon_stream;
namespace dc = density_based_air_shower_photon_classification;

static const char USAGE[] =
R"(Classify air-shower-photons based on the photon-density in the stream.

    Usage:
      phs.table
      phs.table  (-h | --help)
      phs.table  --version

    Options:
      -h --help           Show this screen.
      --version           Show version.

)";

int main(int argc, char* argv[]) {
    std::map<std::string, docopt::value> args = docopt::docopt(
        USAGE,
        { argv + 1, argv + argc },
        true,        // show help if requested
        "phs.cluster 0.0.1");  // version string

    std::array<
        std::vector<std::vector<uint64_t>>,
        ps::NUMBER_OF_PIXELS
    > neit = dc::xyt_neighborhood();

    while (true) {
        ps::ObservationEvent event = ps::read_ObservationEvent_from_file(
            std::cin);

        if (!event.descriptor.is_valid())
            break;

        std::vector<uint64_t> density = dc::photon_density(
            event.photon_stream.raw, neit);

        std::vector<bool> mask = dc::high_photon_density_mask(density);

        std::vector<uint8_t> raw_air_shower_photons = ps::in_mask(
            event.photon_stream.raw,
            mask);

        event.photon_stream.raw = raw_air_shower_photons;
        ps::append_ObservationEvent_to_file(event, std::cout);
    }

    return 0;
}
