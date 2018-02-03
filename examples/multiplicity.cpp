// Copyright 2018 Sebastian Achim Mueller
//
// Compile:
// g++ docopt/docopt.cpp multiplicity.cpp -o phs.multiplicity -std=gnu++11

#include <stdio.h>
#include <string.h>
#include <array>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "../photon_stream.h"
#include "docopt/docopt.h"

namespace ps = photon_stream;

static const char USAGE[] =
R"(Estimate the multiplicity of pulses. This is the intensity of different
photon-arrival-time-cluster-sizes. Reads phs events from stdin and writes jsonl
to stdout.

    Usage:
      phs.multiplicity
      phs.multiplicity  (-h | --help)
      phs.multiplicity  --version

    Options:
      -h --help           Show this screen.
      --version           Show version.
)";

const uint64_t NUM_MULTIPLICITY_BINS = 100;

void multiplicity(
    std::array<int, NUM_MULTIPLICITY_BINS> *m,
    const std::vector<uint8_t> &raw,
    const int radius_slices
) {
    std::vector<uint8_t> raw_sorted_pixel = raw;
    std::sort(raw_sorted_pixel.begin(), raw_sorted_pixel.end());

    std::vector<int> clusters;
    clusters.push_back(0);

    int cluster = 0;
    for (int p = 0; p < raw_sorted_pixel.size(); p++) {
        int next_p = p + 1;
        int arrival = raw_sorted_pixel[p];
        if (next_p < raw_sorted_pixel.size()) {
            int next_arrival = raw_sorted_pixel[next_p];
            if ((next_arrival - arrival) <= radius_slices) {
                clusters.at(cluster)++;
            } else {
                cluster++;
                clusters.push_back(0);
            }
        } else {
            cluster++;
            clusters.push_back(0);
        }
    }

    for (int c = 0; c < clusters.size() - 1; c++) {
        if (clusters.at(c) < NUM_MULTIPLICITY_BINS) {
            m->at(clusters.at(c))++;
        }
    }
}


int main(int argc, char* argv[]) {
    std::map<std::string, docopt::value> args = docopt::docopt(
        USAGE,
        { argv + 1, argv + argc },
        true,        // show help if requested
        "mct 0.0");  // version string

    const int coincidence_radius_slices = 2;

    while (true) {
        ps::ObservationEvent event = ps::read_ObservationEvent_from_file(
            std::cin);

        if (!event.descriptor.is_valid())
            break;

        std::array<std::vector<uint8_t>, ps::NUMBER_OF_PIXELS> lol =
            ps::list_of_lists_representation(event.photon_stream.raw);

        int total_pixels = 0;
        std::array<int, NUM_MULTIPLICITY_BINS> m;
        for (int i = 0; i < m.size(); i++) {m[i] = 0;}

        for (int chid = 0; chid < lol.size(); chid++) {
            multiplicity(&m, lol.at(chid), coincidence_radius_slices);
            total_pixels++;
        }

        double exposure_time = (
            static_cast<double>(total_pixels)*
            static_cast<double>(ps::NUMBER_OF_TIME_SLICES)*
            ps::TIME_SLICE_DURATION_S);

        std::cout << "{";
        std::cout << "\"Night\":" << event.id.night << ",";
        std::cout << "\"Run\":" << event.id.run << ",";
        std::cout << "\"Event\":" << event.id.event << ",";
        std::cout << "\"UnixTime_s_us\":[";
        std::cout << event.info.unix_time_s << ",";
        std::cout << event.info.unix_time_us << "],";
        std::cout << "\"Trigger\":" << event.info.trigger_type << ",";
        std::cout << "\"Az_deg\":" << event.pointing.az << ",";
        std::cout << "\"Zd_deg\":" << event.pointing.zd << ",";
        std::cout << "\"ExposureTime_s\":" << exposure_time << ",";

        std::cout << "\"Multiplicity\":[";
        for (int i = 0; i < m.size(); i++) {
            std::cout << m[i];
            if (i < m.size() - 1)
                std::cout << ",";
        }
        std::cout << "]";
        std::cout << "}\n";
    }

    return 0;
}
