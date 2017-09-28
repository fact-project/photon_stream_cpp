// compile using:
// g++ docopt/docopt.cpp example_table.cpp -o phs.table -std=gnu++11

#include <stdio.h>
#include <string.h>
#include <array>
#include "photon_stream.h"
#include "docopt/docopt.h"
#include <fstream>
#include <iostream>

namespace ps = photon_stream;

static const char USAGE[] =
R"(Show FACT photon-stream event overview in a table on stdout. Reads in phs
files from stdin. 

    Usage:
      phs.table [--trigger=INT]
      phs.table  (-h | --help)
      phs.table  --version

    Options:
      -t --trigger=INT    Only show certain trigger type.
      -h --help           Show this screen.
      --version           Show version.
      
)";

void print_event_info_line(ps::ObservationEvent &event) {
    printf(
        "%05d %03d %5d %6d  %3.2f  %3.2f  %10.6f  %6d\n",  
        event.id.night,
        event.id.run,
        event.id.event,
        event.info.trigger_type,
        event.pointing.az,
        event.pointing.zd,
        float(event.info.unix_time_s) + 1e-6*float(event.info.unix_time_us),
        event.photon_stream.number_of_photons()
    );
};

int main(int argc, char* argv[]) {

    std::map<std::string, docopt::value> args = docopt::docopt(
        USAGE,
        { argv + 1, argv + argc },
        true,        // show help if requested
        "mct 0.0"
    );  // version string

    printf("night    run event trigger  Az[deg] ZD[deg]  UnixTime[s]   photons\n");
    printf("------------------------------------------------------------------\n");
    

    while(true) {
        ps::ObservationEvent event = ps::read_ObservationEvent_from_file(std::cin);

        if(!event.descriptor.is_valid())
            break;

        if(args.find("--trigger")->second) {
            if(
                std::stoi(args.find("--trigger")->second.asString()) == 
                event.info.trigger_type
            ) {
                print_event_info_line(event);
            }
        }else{
            print_event_info_line(event);     
        }
    }
    return 0;
};