// FACT--Photon-Stream
// Copyright (C), (2017, ), Sebastian Achim Mueller for the FACT Collaboration
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>

#ifndef PHOTON_STREAM_H_
#define PHOTON_STREAM_H_

#include <math.h>
#include <stdint.h>
#include <vector>
#include <array>
#include <fstream>
#include <iostream>

namespace photon_stream {

const uint8_t NUMBER_OF_TIME_SLICES_OFFSET_AFTER_BEGIN_OF_ROI = 30;
const uint8_t NUMBER_OF_TIME_SLICES = 100;
const uint32_t NUMBER_OF_PIXELS = 1440;
const uint32_t NUMBER_OF_PHOTONS_IN_PIXEL_BEFORE_SATURATION = 500;
const uint8_t NEXT_PIXEL_MARKER = 255;
const float TIME_SLICE_DURATION_S = 0.5e-9;
const uint8_t OBSERVATION_EVENT_TYPE_KEY = 0;
const uint8_t SIMULATION_EVENT_TYPE_KEY = 1;
const uint8_t PASS_VERSION = 4;
const uint8_t MAGIC_DESCRIPTOR_1 = 'p';
const uint8_t MAGIC_DESCRIPTOR_2 = 'h';
const uint8_t MAGIC_DESCRIPTOR_3 = 's';

//                         whole time series
//  |.......................................................................|
//  |                                                                       |
//  |         |................ extraction window .................|        |
//  |         | <---------- length = 225 ------------------------> |        |
//  |         |                                                    |        |
//  |         |       |.. output window ..|                        |        |
//  0        20       | <- length=100 ->  |                       245      300
//                   30                  130
//
// [in 2GHz slices]
//
// - whole time series
//     The full 300 slices (150ns) Region Of Interest (ROI) of the FACT camera.
//
// - extraction window
//     The timewindow where single pulses are searched for and extracted.
//
// - output window
//     The photon-stream output time window 100 slices (50ns)
//
// see also: https://github.com/fact-project/fact-tools/blob/master/src/main/java/fact/photonstream/SinglePulseExtraction.java

void append_float32(const float &v, std::ostream &fout) {
    fout.write(reinterpret_cast<char*>(&v), sizeof(v));
}

float read_float32(std::istream &fin) {
    float v;
    fin.read(reinterpret_cast<char*>(&v), sizeof(v));
    return v;
}

void append_uint32(const uint32_t &v, std::ostream &fout) {
    fout.write(reinterpret_cast<char*>(&v), sizeof(v));
}
uint32_t read_uint32(std::istream &fin) {
    uint32_t v;
    fin.read(reinterpret_cast<char*>(&v), sizeof(v));
    return v;
}

void append_uint16(const uint16_t &v, std::ostream &fout) {
    fout.write(reinterpret_cast<char*>(&v), sizeof(v));
}
uint16_t read_uint16(std::istream &fin) {
    uint16_t v;
    fin.read(reinterpret_cast<char*>(&v), sizeof(v));
    return v;
}

void append_uint8(const uint8_t &v, std::ostream &fout) {
    fout.write(reinterpret_cast<char*>(&v), sizeof(v));
}
uint8_t read_uint8(std::istream &fin) {
    uint8_t v;
    fin.read(reinterpret_cast<char*>(&v), sizeof(v));
    return v;
}

//------------------------------------------------------------------------------
struct Descriptor {
    uint8_t magic_1;
    uint8_t magic_2;
    uint8_t magic_3;
    uint8_t pass_version;
    uint8_t event_type;

    bool is_valid() {
        return (magic_1 == MAGIC_DESCRIPTOR_1 &&
                magic_2 == MAGIC_DESCRIPTOR_2 &&
                magic_3 == MAGIC_DESCRIPTOR_3);
    }
};

Descriptor read_Descriptor_from_file(std::istream &fin) {
    Descriptor d;
    d.magic_1 = read_uint8(fin);
    d.magic_2 = read_uint8(fin);
    d.magic_3 = read_uint8(fin);
    d.pass_version = read_uint8(fin);
    d.event_type = read_uint8(fin);
    return d;
}

void append_Descriptor_to_file(const Descriptor &d, std::ostream &fout) {
    append_uint8(d.magic_1, fout);
    append_uint8(d.magic_2, fout);
    append_uint8(d.magic_3, fout);
    append_uint8(d.pass_version, fout);
    append_uint8(d.event_type, fout);
}

//------------------------------------------------------------------------------
struct ObservationIdentifier {
    uint32_t night;
    uint32_t run;
    uint32_t event;
};

ObservationIdentifier read_ObservationIdentifier_from_file(std::istream &fin) {
    ObservationIdentifier obsid;
    obsid.night = read_uint32(fin);
    obsid.run = read_uint32(fin);
    obsid.event = read_uint32(fin);
    return obsid;
}

void append_ObservationIdentifier_to_file(
    const ObservationIdentifier &obsid,
    std::ostream &fout
) {
    append_uint32(obsid.night, fout);
    append_uint32(obsid.run, fout);
    append_uint32(obsid.event, fout);
}

//------------------------------------------------------------------------------
struct ObservationInformation {
    uint32_t unix_time_s;
    uint32_t unix_time_us;
    uint32_t trigger_type;
};

ObservationInformation read_ObservationInformation_from_file(
    std::istream &fin
) {
    ObservationInformation obsinfo;
    obsinfo.unix_time_s = read_uint32(fin);
    obsinfo.unix_time_us = read_uint32(fin);
    obsinfo.trigger_type = read_uint32(fin);
    return obsinfo;
}

void append_ObservationInformation_to_file(
    const ObservationInformation &obsinfo,
    std::ostream &fout
) {
    append_uint32(obsinfo.unix_time_s , fout);
    append_uint32(obsinfo.unix_time_us, fout);
    append_uint32(obsinfo.trigger_type, fout);
}

//------------------------------------------------------------------------------
struct SimulationIdentifier {
    uint32_t run;
    uint32_t event;
    uint32_t reuse;
};

SimulationIdentifier read_SimulationIdentifier_from_file(std::istream &fin) {
    SimulationIdentifier simid;
    simid.run = read_uint32(fin);
    simid.event = read_uint32(fin);
    simid.reuse = read_uint32(fin);
    return simid;
}

void append_SimulationIdentifier_to_file(
    const SimulationIdentifier &simid,
    std::ostream &fout
) {
    append_uint32(simid.run , fout);
    append_uint32(simid.event, fout);
    append_uint32(simid.reuse, fout);
}

//------------------------------------------------------------------------------
struct Pointing {
    float zd;
    float az;
};

Pointing read_Pointing_from_file(std::istream &fin) {
    Pointing p;
    p.zd = read_float32(fin);
    p.az = read_float32(fin);
    return p;
}

void append_Pointing_to_file(const Pointing &p, std::ostream &fout) {
    append_float32(p.zd, fout);
    append_float32(p.az, fout);
}

//------------------------------------------------------------------------------
#define raw_stream std::vector<uint8_t>
#define image std::array<uint64_t, NUMBER_OF_PIXELS>
#define image_sequence std::array<image, NUMBER_OF_TIME_SLICES>
#define list_of_lists std::array<std::vector<uint8_t>, NUMBER_OF_PIXELS>


list_of_lists list_of_lists_representation(raw_stream &raw) {
    list_of_lists lol;
    uint32_t chid = 0;
    for (uint32_t i = 0; i < raw.size(); i++) {
        if (raw[i] == NEXT_PIXEL_MARKER) {
            chid++;
        } else {
            lol[chid].push_back(raw[i]);
        }
    }
    return lol;
}


image list_of_lists_integral(const list_of_lists &l) {
    image img;
    for (uint32_t i = 0; i < l.size(); i++) {
        img[i] = l[i].size();
    }
    return img;
}


image image_integral(raw_stream &raw) {
    list_of_lists lol = list_of_lists_representation(raw);
    return list_of_lists_integral(lol);
}


image_sequence image_sequence_representation(raw_stream &raw) {
    image_sequence seq;
    uint32_t chid = 0;
    for (uint32_t i = 0; i < raw.size(); i++) {
        if (raw[i] == NEXT_PIXEL_MARKER) {
            chid++;
        } else {
            uint8_t idx =
                raw[i] - NUMBER_OF_TIME_SLICES_OFFSET_AFTER_BEGIN_OF_ROI;
            seq[idx][chid]++;
        }
    }
    return seq;
}


struct PhotonStream {
    raw_stream raw;
    std::vector<uint16_t> saturated_pixels;

    uint32_t number_of_photons() {
        return raw.size() - NUMBER_OF_PIXELS;
    }

    bool is_adc_saturaded() {
        return saturated_pixels.size() > 0;
    }

    bool is_single_pulse_extractor_saturated() {
        image img = image_integral(raw);
        for (uint32_t chid = 0; chid < img.size(); chid++) {
            if (img.at(chid) > NUMBER_OF_PHOTONS_IN_PIXEL_BEFORE_SATURATION)
                return true;
        }
        return false;
    }

    bool is_saturated() {
        return is_adc_saturaded() || is_single_pulse_extractor_saturated();
    }
};


PhotonStream read_PhotonStream_from_file(std::istream &fin) {
    PhotonStream phs;
    uint32_t number_of_pixels_plus_number_of_photons = read_uint32(fin);

    phs.raw.resize(number_of_pixels_plus_number_of_photons);
    fin.read(
        reinterpret_cast<char*>(&phs.raw[0]),
        number_of_pixels_plus_number_of_photons);

    uint16_t number_of_saturated_pixels = read_uint16(fin);

    phs.saturated_pixels.resize(number_of_saturated_pixels);
    fin.read(
        reinterpret_cast<char*>(&phs.saturated_pixels[0]),
        sizeof(uint16_t)*number_of_saturated_pixels);
    return phs;
}

void append_PhotonStream_to_file(const PhotonStream &phs, std::ostream &fout) {
    uint32_t number_of_pixels_plus_number_of_photons = phs.raw.size();
    append_uint32(number_of_pixels_plus_number_of_photons, fout);
    fout.write(
        reinterpret_cast<char*>(phs.raw.data()),
        number_of_pixels_plus_number_of_photons);

    uint16_t number_of_saturated_pixels = phs.saturated_pixels.size();
    append_uint16(number_of_saturated_pixels, fout);
    fout.write(
        reinterpret_cast<char*>(phs.saturated_pixels.data()),
        number_of_saturated_pixels);
}


//------------------------------------------------------------------------------
struct ObservationEvent {
    Descriptor descriptor;
    ObservationIdentifier id;
    ObservationInformation info;
    Pointing pointing;
    PhotonStream photon_stream;
};

ObservationEvent read_ObservationEvent_from_file(std::istream &fin) {
    ObservationEvent evt;
    evt.descriptor = read_Descriptor_from_file(fin);
    if (evt.descriptor.event_type != OBSERVATION_EVENT_TYPE_KEY) {
        throw std::runtime_error("Expected observation key");
    }
    evt.id = read_ObservationIdentifier_from_file(fin);
    evt.info = read_ObservationInformation_from_file(fin);
    evt.pointing = read_Pointing_from_file(fin);
    evt.photon_stream = read_PhotonStream_from_file(fin);
    return evt;
}

void append_ObservationEvent_to_file(
    const ObservationEvent evt,
    std::ostream &fout
) {
    append_Descriptor_to_file(evt.descriptor, fout);
    append_ObservationIdentifier_to_file(evt.id, fout);
    append_ObservationInformation_to_file(evt.info, fout);
    append_PhotonStream_to_file(evt.photon_stream, fout);
}


//------------------------------------------------------------------------------
struct SimulationEvent {
    Descriptor descriptor;
    SimulationIdentifier id;
    Pointing pointing;
    PhotonStream photon_stream;
};

SimulationEvent read_SimulationEvent_from_file(std::istream &fin) {
    SimulationEvent evt;
    evt.descriptor = read_Descriptor_from_file(fin);
    if (evt.descriptor.event_type != SIMULATION_EVENT_TYPE_KEY) {
        throw std::runtime_error("Expected simulation key");
    }
    evt.id = read_SimulationIdentifier_from_file(fin);
    evt.pointing = read_Pointing_from_file(fin);
    evt.photon_stream = read_PhotonStream_from_file(fin);
    return evt;
}

void append_SimulationEvent_to_file(
    const SimulationEvent evt,
    std::ostream &fout
) {
    append_Descriptor_to_file(evt.descriptor, fout);
    append_SimulationIdentifier_to_file(evt.id, fout);
    append_PhotonStream_to_file(evt.photon_stream, fout);
}

//------------------------------------------------------------------------------
}  // namespace photon_stream

#endif  // PHOTON_STREAM_H_