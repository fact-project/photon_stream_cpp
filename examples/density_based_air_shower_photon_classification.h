// Copyright 2018, Sebastian Achim Mueller

#ifndef EXAMPLES_DENSITY_BASED_AIR_SHOWER_PHOTON_CLASSIFICATION_H_
#define EXAMPLES_DENSITY_BASED_AIR_SHOWER_PHOTON_CLASSIFICATION_H_

#include <stdint.h>
#include <array>
#include <algorithm>
#include <vector>
#include "../photon_stream.h"

namespace density_based_air_shower_photon_classification {

std::array<double, photon_stream::NUMBER_OF_PIXELS> pixel_pos_x_deg = {{0.334,0.389,0.389,0.445,0.501,0.501,0.556,0.612,0.612,-0.0,0.056,0.056,0.111,0.167,0.167,0.223,0.278,0.278,0.835,0.779,0.779,0.723,0.668,0.668,0.612,0.556,0.556,0.501,0.445,0.445,0.389,0.334,0.334,0.278,0.223,0.223,1.335,1.28,1.28,1.224,1.168,1.168,1.113,1.057,1.057,1.558,1.502,1.447,1.391,1.447,1.391,1.335,1.28,1.224,1.224,1.168,1.113,1.057,1.113,1.057,1.002,0.946,0.89,1.002,0.946,0.89,0.89,0.835,0.779,0.723,0.723,0.668,1.502,1.447,1.447,1.391,1.335,1.335,1.28,1.224,1.224,1.78,1.725,1.669,1.614,1.725,1.669,1.614,1.558,1.502,1.168,1.113,1.113,1.057,1.002,1.002,0.946,0.89,0.89,0.835,0.779,0.779,0.723,0.668,0.668,0.612,0.556,0.556,1.002,0.946,0.946,0.89,0.835,0.835,0.779,0.723,0.723,0.668,0.612,0.612,0.556,0.501,0.501,0.445,0.389,0.389,0.334,0.278,0.278,0.223,0.167,0.167,0.111,0.056,0.056,0.501,0.445,0.445,0.389,0.334,0.334,0.278,0.223,0.223,2.059,2.059,2.003,1.947,1.892,1.892,1.836,1.78,1.725,2.003,1.947,1.892,1.836,1.836,1.78,1.725,1.669,1.558,1.669,1.614,1.614,1.558,1.502,1.502,1.447,1.391,1.391,1.335,1.28,1.28,1.224,1.168,1.168,1.113,1.057,1.057,1.002,0.946,0.946,0.89,0.835,0.835,0.779,0.723,0.723,0.668,0.612,0.612,0.556,0.501,0.501,0.445,0.389,0.389,0.334,0.278,0.278,0.223,0.167,0.167,0.111,0.056,0.056,0.167,0.111,0.111,0.056,-0.0,-0.0,-0.056,-0.111,-0.111,2.17,2.17,2.114,2.059,2.114,2.059,2.003,1.947,1.892,1.836,1.78,1.78,1.725,1.669,1.669,1.614,1.558,1.558,1.502,1.447,1.447,1.391,1.335,1.335,1.28,1.224,1.224,1.168,1.113,1.113,1.057,1.002,1.002,0.946,0.89,0.89,0.501,0.445,0.445,0.389,0.334,0.334,0.278,0.223,0.223,0.835,0.779,0.779,0.723,0.668,0.668,0.612,0.556,0.556,0.668,0.612,0.612,0.556,0.501,0.501,0.445,0.389,0.389,0.334,0.278,0.278,0.223,0.167,0.167,0.111,0.056,0.056,2.003,1.947,1.947,1.892,1.836,1.836,1.78,1.725,1.725,1.669,1.614,1.614,1.558,1.502,1.502,1.447,1.391,1.391,1.335,1.28,1.28,1.224,1.168,1.168,1.113,1.057,1.057,1.002,0.946,0.946,0.89,0.835,0.835,0.779,0.723,0.723,1.836,1.78,1.78,1.725,1.669,1.669,1.614,1.558,1.558,2.17,2.114,2.114,2.059,2.003,2.003,1.947,1.892,1.892,1.502,1.447,1.447,1.391,1.335,1.335,1.28,1.224,1.224,1.168,1.113,1.113,1.057,1.002,1.002,0.946,0.89,0.89,0.835,0.779,0.779,0.723,0.668,0.668,0.612,0.556,0.556,0.501,0.445,0.445,0.389,0.334,0.334,0.278,0.223,0.223,0.334,0.278,0.278,0.223,0.167,0.167,0.111,0.056,0.056,0.167,0.111,0.111,0.056,-0.0,-0.0,-0.056,-0.111,-0.111,1.002,0.946,0.946,0.89,0.835,0.835,0.779,0.723,0.723,0.668,0.612,0.612,0.556,0.501,0.501,0.445,0.389,0.389,0.501,0.445,0.445,0.389,0.334,0.334,0.278,0.223,0.223,0.167,0.111,0.111,0.056,-0.0,-0.0,-0.056,-0.111,-0.111,2.17,2.17,2.114,2.059,2.114,2.059,2.003,1.947,1.892,2.003,1.947,1.947,1.892,1.836,1.836,1.78,1.725,1.725,1.669,1.614,1.614,1.558,1.502,1.502,1.447,1.391,1.391,1.335,1.28,1.28,1.224,1.168,1.168,1.113,1.057,1.057,2.059,2.059,2.003,1.947,1.892,1.892,1.836,1.78,1.725,1.836,1.78,1.78,1.725,1.669,1.669,1.614,1.558,1.558,1.502,1.447,1.447,1.391,1.335,1.335,1.28,1.224,1.224,1.168,1.113,1.113,1.057,1.002,1.002,0.946,0.89,0.89,0.668,0.612,0.612,0.556,0.501,0.501,0.445,0.389,0.389,0.835,0.779,0.779,0.723,0.668,0.668,0.612,0.556,0.556,0.501,0.445,0.445,0.389,0.334,0.334,0.278,0.223,0.223,0.334,0.278,0.278,0.223,0.167,0.167,0.111,0.056,0.056,2.003,1.947,1.892,1.836,1.836,1.78,1.725,1.669,1.558,1.669,1.614,1.614,1.558,1.502,1.502,1.447,1.391,1.391,1.335,1.28,1.28,1.224,1.168,1.168,1.113,1.057,1.057,1.002,0.946,0.946,0.89,0.835,0.835,0.779,0.723,0.723,1.78,1.725,1.669,1.614,1.725,1.669,1.614,1.558,1.502,1.502,1.447,1.447,1.391,1.335,1.335,1.28,1.224,1.224,1.168,1.113,1.113,1.057,1.002,1.002,0.946,0.89,0.89,0.835,0.779,0.779,0.723,0.668,0.668,0.612,0.556,0.556,1.558,1.502,1.447,1.391,1.447,1.391,1.335,1.28,1.224,1.335,1.28,1.28,1.224,1.168,1.168,1.113,1.057,1.057,1.224,1.168,1.113,1.057,1.113,1.057,1.002,0.946,0.89,1.002,0.946,0.946,0.89,0.835,0.835,0.779,0.723,0.723,0.668,0.612,0.612,0.556,0.501,0.501,0.445,0.389,0.389,0.334,0.278,0.278,0.223,0.167,0.167,0.111,0.056,0.056,0.501,0.445,0.445,0.389,0.334,0.334,0.278,0.223,0.223,0.167,0.111,0.111,0.056,-0.0,-0.0,-0.056,-0.111,-0.111,1.002,0.946,0.89,0.89,0.835,0.779,0.723,0.723,0.668,0.835,0.779,0.779,0.723,0.668,0.668,0.612,0.556,0.556,0.334,0.389,0.389,0.445,0.501,0.501,0.556,0.612,0.612,-0.0,0.056,0.056,0.111,0.167,0.167,0.223,0.278,0.278,-0.668,-0.612,-0.612,-0.556,-0.501,-0.501,-0.445,-0.389,-0.389,-0.334,-0.278,-0.278,-0.223,-0.167,-0.167,-0.111,-0.056,-0.056,-0.501,-0.556,-0.556,-0.612,-0.668,-0.668,-0.723,-0.779,-0.779,-0.167,-0.223,-0.223,-0.278,-0.334,-0.334,-0.389,-0.445,-0.445,-1.002,-1.057,-1.057,-1.113,-1.168,-1.168,-1.224,-1.28,-1.28,-1.224,-1.335,-1.391,-1.447,-1.335,-1.391,-1.447,-1.502,-1.502,-0.835,-0.89,-0.946,-1.002,-1.057,-1.113,-1.168,-1.224,-1.28,-0.723,-0.779,-0.835,-0.89,-0.89,-0.946,-1.002,-1.057,-1.113,-1.168,-1.224,-1.224,-1.28,-1.335,-1.335,-1.391,-1.447,-1.447,-1.502,-1.558,-1.558,-1.614,-1.558,-1.614,-1.669,-1.669,-1.725,-0.835,-0.89,-0.89,-0.946,-1.002,-1.002,-1.057,-1.113,-1.113,-0.501,-0.556,-0.556,-0.612,-0.668,-0.668,-0.723,-0.779,-0.779,-0.668,-0.723,-0.723,-0.779,-0.835,-0.835,-0.89,-0.946,-0.946,-0.334,-0.389,-0.389,-0.445,-0.501,-0.501,-0.556,-0.612,-0.612,-0.167,-0.223,-0.223,-0.278,-0.334,-0.334,-0.389,-0.445,-0.445,-0.0,-0.056,-0.056,-0.111,-0.167,-0.167,-0.223,-0.278,-0.278,-1.725,-1.78,-1.836,-1.892,-1.947,-1.947,-2.003,-2.003,-2.059,-1.669,-1.725,-1.669,-1.836,-1.78,-1.78,-1.836,-1.725,-1.892,-1.335,-1.391,-1.391,-1.447,-1.502,-1.502,-1.558,-1.614,-1.614,-1.002,-1.057,-1.057,-1.113,-1.168,-1.168,-1.224,-1.28,-1.28,-0.668,-0.723,-0.723,-0.779,-0.835,-0.835,-0.89,-0.946,-0.946,-0.334,-0.389,-0.389,-0.445,-0.501,-0.501,-0.556,-0.612,-0.612,-0.0,-0.056,-0.056,-0.111,-0.167,-0.167,-0.223,-0.278,-0.278,0.167,0.111,0.111,0.056,-0.0,-0.0,-0.056,-0.111,-0.111,-1.836,-1.892,-1.892,-1.947,-2.003,-2.059,-2.059,-2.114,-2.17,-1.502,-1.558,-1.558,-1.614,-1.669,-1.669,-1.725,-1.78,-1.78,-1.168,-1.224,-1.224,-1.28,-1.335,-1.335,-1.391,-1.447,-1.447,-0.835,-0.89,-0.89,-0.946,-1.002,-1.002,-1.057,-1.113,-1.113,-0.501,-0.556,-0.556,-0.612,-0.668,-0.668,-0.723,-0.779,-0.779,-0.167,-0.223,-0.223,-0.278,-0.334,-0.334,-0.389,-0.445,-0.445,-0.334,-0.389,-0.389,-0.445,-0.501,-0.501,-0.556,-0.612,-0.612,-0.0,-0.056,-0.056,-0.111,-0.167,-0.167,-0.223,-0.278,-0.278,-1.669,-1.725,-1.725,-1.78,-1.836,-1.836,-1.892,-1.947,-1.947,-1.335,-1.391,-1.391,-1.447,-1.502,-1.502,-1.558,-1.614,-1.614,-1.002,-1.057,-1.057,-1.113,-1.168,-1.168,-1.224,-1.28,-1.28,-0.668,-0.723,-0.723,-0.779,-0.835,-0.835,-0.89,-0.946,-0.946,-1.836,-1.892,-1.892,-1.947,-2.003,-2.003,-2.059,-2.114,-2.17,-2.003,-2.003,-2.059,-2.114,-2.059,-2.114,-2.114,-2.17,-2.17,-1.502,-1.558,-1.558,-1.614,-1.669,-1.669,-1.725,-1.78,-1.78,-1.168,-1.224,-1.224,-1.28,-1.335,-1.335,-1.391,-1.447,-1.447,-0.835,-0.89,-0.89,-0.946,-1.002,-1.002,-1.057,-1.113,-1.113,-0.501,-0.556,-0.556,-0.612,-0.668,-0.668,-0.723,-0.779,-0.779,-0.167,-0.223,-0.223,-0.278,-0.334,-0.334,-0.389,-0.445,-0.445,-0.0,-0.056,-0.056,-0.111,-0.167,-0.167,-0.223,-0.278,-0.278,-0.668,-0.723,-0.723,-0.779,-0.835,-0.835,-0.89,-0.946,-0.946,-0.334,-0.389,-0.389,-0.445,-0.501,-0.501,-0.556,-0.612,-0.612,-0.167,-0.223,-0.223,-0.278,-0.334,-0.334,-0.389,-0.445,-0.445,0.167,0.111,0.111,0.056,-0.0,-0.0,-0.056,-0.111,-0.111,-1.836,-1.892,-1.892,-1.947,-2.003,-2.059,-2.059,-2.114,-2.17,-1.669,-1.725,-1.725,-1.78,-1.836,-1.836,-1.892,-1.947,-1.947,-1.335,-1.391,-1.391,-1.447,-1.502,-1.502,-1.558,-1.614,-1.614,-1.002,-1.057,-1.057,-1.113,-1.168,-1.168,-1.224,-1.28,-1.28,-1.725,-1.78,-1.836,-1.892,-1.947,-1.947,-2.003,-2.003,-2.059,-1.502,-1.558,-1.558,-1.614,-1.669,-1.669,-1.725,-1.78,-1.78,-1.168,-1.224,-1.224,-1.28,-1.335,-1.335,-1.391,-1.447,-1.447,-0.835,-0.89,-0.89,-0.946,-1.002,-1.002,-1.057,-1.113,-1.113,-0.334,-0.389,-0.389,-0.445,-0.501,-0.501,-0.556,-0.612,-0.612,-0.501,-0.556,-0.556,-0.612,-0.668,-0.668,-0.723,-0.779,-0.779,-0.167,-0.223,-0.223,-0.278,-0.334,-0.334,-0.389,-0.445,-0.445,-0.0,-0.056,-0.056,-0.111,-0.167,-0.167,-0.223,-0.278,-0.278,-1.669,-1.669,-1.725,-1.836,-1.725,-1.78,-1.78,-1.836,-1.892,-1.335,-1.391,-1.391,-1.447,-1.502,-1.502,-1.558,-1.614,-1.614,-1.002,-1.057,-1.057,-1.113,-1.168,-1.168,-1.224,-1.28,-1.28,-0.668,-0.723,-0.723,-0.779,-0.835,-0.835,-0.89,-0.946,-0.946,-1.502,-1.558,-1.558,-1.614,-1.558,-1.614,-1.669,-1.669,-1.725,-1.168,-1.224,-1.224,-1.28,-1.335,-1.335,-1.391,-1.447,-1.447,-0.835,-0.89,-0.89,-0.946,-1.002,-1.002,-1.057,-1.113,-1.113,-0.501,-0.556,-0.556,-0.612,-0.668,-0.668,-0.723,-0.779,-0.779,-1.224,-1.335,-1.391,-1.447,-1.335,-1.391,-1.447,-1.502,-1.502,-1.002,-1.057,-1.057,-1.113,-1.168,-1.168,-1.224,-1.28,-1.28,-0.835,-0.89,-0.946,-1.002,-1.057,-1.113,-1.168,-1.224,-1.28,-0.668,-0.723,-0.723,-0.779,-0.835,-0.835,-0.89,-0.946,-0.946,-0.334,-0.389,-0.389,-0.445,-0.501,-0.501,-0.556,-0.612,-0.612,-0.0,-0.056,-0.056,-0.111,-0.167,-0.167,-0.223,-0.278,-0.278,-0.167,-0.223,-0.223,-0.278,-0.334,-0.334,-0.389,-0.445,-0.445,0.167,0.111,0.111,0.056,-0.0,-0.0,-0.056,-0.111,-0.111,-0.723,-0.779,-0.835,-0.89,-0.89,-0.946,-1.002,-1.057,-1.113,-0.501,-0.556,-0.556,-0.612,-0.668,-0.668,-0.723,-0.779,-0.779,-0.668,-0.612,-0.612,-0.556,-0.501,-0.501,-0.445,-0.389,-0.389,-0.334,-0.278,-0.278,-0.223,-0.167,-0.167,-0.111,-0.056,-0.056}};
std::array<double, photon_stream::NUMBER_OF_PIXELS> pixel_pos_y_deg = {{2.024,2.12,1.927,2.024,2.12,1.927,2.024,2.12,1.927,2.024,2.12,1.927,2.024,2.12,1.927,2.024,2.12,1.927,1.735,1.638,1.831,1.735,1.638,1.831,1.735,1.638,1.831,1.735,1.638,1.831,1.735,1.638,1.831,1.735,1.638,1.831,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.542,1.45,1.349,1.638,1.542,1.638,1.735,1.638,1.831,1.735,1.831,1.927,1.638,1.735,1.638,1.735,1.638,1.831,1.927,1.831,2.024,1.927,2.024,1.927,2.12,2.024,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,1.253,1.156,1.253,1.156,1.349,1.45,1.349,1.253,1.349,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,0.579,0.771,0.674,0.771,0.674,0.867,0.771,0.867,0.771,0.867,0.964,1.061,0.964,1.156,1.061,0.964,1.061,1.061,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,0.193,0.385,0.289,0.193,0.482,0.385,0.482,0.579,0.482,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.385,-0.193,-0.289,-0.193,-0.482,-0.385,-0.482,-0.579,-0.482,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.771,-0.579,-0.674,-0.771,-0.867,-0.674,-0.771,-0.867,-0.771,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-1.061,-0.964,-1.156,-1.061,-0.964,-1.061,-1.061,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-1.253,-1.156,-1.253,-1.156,-1.349,-1.45,-1.349,-1.253,-1.349,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.45,-1.542,-1.45,-1.349,-1.638,-1.542,-1.638,-1.735,-1.638,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.831,-1.735,-1.831,-1.927,-1.638,-1.735,-1.638,-1.735,-1.638,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.735,-1.831,-1.638,-1.735,-1.831,-1.638,-1.735,-1.831,-1.638,-1.735,-1.831,-1.638,-1.735,-1.831,-1.638,-1.735,-1.831,-1.638,-1.831,-1.927,-2.024,-1.831,-1.927,-2.024,-2.12,-1.927,-2.024,-1.735,-1.831,-1.638,-1.735,-1.831,-1.638,-1.735,-1.831,-1.638,-2.024,-1.927,-2.12,-2.024,-1.927,-2.12,-2.024,-1.927,-2.12,-2.024,-1.927,-2.12,-2.024,-1.927,-2.12,-2.024,-1.927,-2.12,-2.024,-1.927,-2.12,-2.024,-1.927,-2.12,-2.024,-1.927,-2.12,-2.024,-1.927,-2.12,-2.024,-1.927,-2.12,-2.024,-1.927,-2.12,-1.735,-1.831,-1.638,-1.735,-1.831,-1.638,-1.735,-1.831,-1.638,-1.735,-1.831,-1.638,-1.735,-1.831,-1.638,-1.735,-1.831,-1.638,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.638,-1.638,-1.542,-1.638,-1.45,-1.349,-1.45,-1.542,-1.349,-1.735,-1.638,-1.735,-1.638,-1.735,-1.638,-1.735,-1.831,-1.735,-1.927,-2.024,-1.927,-2.024,-1.831,-1.927,-1.831,-1.927,-1.831,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.45,-1.349,-1.45,-1.253,-1.349,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-1.45,-1.542,-1.349,-0.771,-0.867,-0.771,-0.867,-0.964,-0.771,-0.867,-0.674,-0.771,-1.061,-0.964,-0.867,-0.964,-1.061,-1.253,-1.156,-1.156,-1.061,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-0.867,-0.964,-0.771,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-1.156,-1.253,-1.061,-0.579,-0.674,-0.482,-0.579,-0.482,-0.579,-0.385,-0.482,-0.385,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.579,-0.674,-0.482,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,-0.289,-0.385,-0.193,0.0,-0.097,0.097,0.0,0.097,0.289,0.193,0.289,0.193,-0.289,-0.097,-0.193,-0.289,0.0,-0.097,0.097,-0.193,0.0,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.0,-0.097,0.097,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.385,0.579,0.482,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.289,0.193,0.385,0.771,0.867,0.771,0.867,0.771,0.964,0.674,0.867,0.771,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.579,0.482,0.674,0.579,0.482,0.674,0.579,0.482,0.674,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,1.061,0.964,0.964,1.156,1.061,1.253,1.156,1.061,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,0.867,0.771,0.964,1.156,1.061,1.253,1.156,1.45,1.349,1.253,1.45,1.349,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,1.156,1.061,1.253,1.638,1.638,1.542,1.638,1.45,1.349,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.735,1.638,1.735,1.638,1.735,1.638,1.735,1.831,1.735,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.45,1.349,1.542,1.735,1.638,1.831,1.735,1.638,1.831,1.735,1.638,1.831,1.735,1.638,1.831,1.735,1.638,1.831,1.735,1.638,1.831,1.927,2.024,1.927,2.024,1.831,1.927,1.831,1.927,1.831,1.735,1.638,1.831,1.735,1.638,1.831,1.735,1.638,1.831,2.024,2.12,1.927,2.024,2.12,1.927,2.024,2.12,1.927,2.024,2.12,1.927,2.024,2.12,1.927,2.024,2.12,1.927}};

std::array<std::vector<std::vector<uint64_t>>, photon_stream::NUMBER_OF_PIXELS>
xyt_neighborhood(
    double epsilon_deg = 0.45,
    double deg_per_second = 0.35e9
) {
    // Neighborhood relations for pixels and time-slices in the photon-stream.
    // This is calculated once before photon_density() is called, and then given
    // as a look-up-table to photon_density().
    double time_radius_seconds = epsilon_deg/deg_per_second;
    int64_t time_radius_slices = static_cast<int64_t>(
        time_radius_seconds/photon_stream::TIME_SLICE_DURATION_S);
    double epsilon_square = epsilon_deg*epsilon_deg;
    std::array<
        std::vector<std::vector<uint64_t>>,
        photon_stream::NUMBER_OF_PIXELS> neighborhood;
    for (uint64_t chid = 0; chid < photon_stream::NUMBER_OF_PIXELS; chid++) {
        double cx = pixel_pos_x_deg[chid];
        double cy = pixel_pos_y_deg[chid];
        double t = 0.0;
        std::vector<std::vector<uint64_t>> t_nei;
        for (
            int64_t nslice = -time_radius_slices;
            nslice <= time_radius_slices;
            nslice++
        ) {
            std::vector<uint64_t> c_nei;
            for (
                uint64_t nchid = 0;
                nchid < photon_stream::NUMBER_OF_PIXELS;
                nchid++
            ) {
                double ncx = pixel_pos_x_deg[nchid];
                double ncy = pixel_pos_y_deg[nchid];
                double nt = deg_per_second*(
                    static_cast<double>(nslice)*
                    photon_stream::TIME_SLICE_DURATION_S);
                double distancne_square = (
                    (cx - ncx)*(cx - ncx) +
                    (cy - ncy)*(cy - ncy) +
                    (t - nt)*(t - nt));
                if (distancne_square <= epsilon_square) {
                    c_nei.push_back(nchid);
                }
            }
            t_nei.push_back(c_nei);
        }
        neighborhood[chid] = t_nei;
    }
    return neighborhood;
}


std::vector<uint64_t> photon_density(
    const std::vector<uint8_t> &raw,
    const std::array<
        std::vector<std::vector<uint64_t>>,
        photon_stream::NUMBER_OF_PIXELS> &xyt_nei
) {
    // Returns for each photon the number of photons in the neighborhood of this
    // photon.
    std::array<
        std::array<uint64_t, photon_stream::NUMBER_OF_PIXELS>,
        photon_stream::NUMBER_OF_TIME_SLICES
    > hist = photon_stream::image_sequence_representation(raw);
    uint64_t num_photons = raw.size() - photon_stream::NUMBER_OF_PIXELS;
    std::vector<uint64_t> dd;
    dd.reserve(num_photons);
    uint64_t num_ts = xyt_nei[0].size();
    uint64_t ts_radius = (num_ts - 1)/2;
    uint64_t chid = 0;
    for (uint64_t i=0; i < raw.size(); i++) {
        if (raw[i] == photon_stream::NEXT_PIXEL_MARKER) {
            chid++;
            continue;
        }
        uint64_t time_slice = (
            raw[i] -
            photon_stream::NUMBER_OF_TIME_SLICES_OFFSET_AFTER_BEGIN_OF_ROI);
        uint64_t dph = 0;
        uint64_t start_slice = 0;
        uint64_t end_slice = photon_stream::NUMBER_OF_TIME_SLICES - 1;
        if (time_slice > ts_radius)
            start_slice = time_slice - ts_radius;
        if (time_slice < (photon_stream::NUMBER_OF_TIME_SLICES - ts_radius))
            end_slice = time_slice + ts_radius;
        for (uint64_t t = start_slice; t <= end_slice; t++) {
            int64_t nt = t - time_slice + ts_radius;
            for (
                uint64_t nchid = 0;
                nchid < xyt_nei[chid][nt].size();
                nchid++
            ) {
                dph += hist[t][xyt_nei[chid][nt][nchid]];
            }
        }
        dd.push_back(dph);
    }
    return dd;
}


std::vector<bool> high_photon_density_mask(
    std::vector<uint64_t> density,
    uint64_t density_threshold = 20
) {
    std::vector<bool> mask(density.size(), false);
    for (uint64_t p = 0; p < density.size(); p++) {
        if (density[p] >= density_threshold) {
            mask.at(p) = true;
        }
    }
    return mask;
}


}  // namespace density_based_air_shower_photon_classification

#endif  // EXAMPLES_DENSITY_BASED_AIR_SHOWER_PHOTON_CLASSIFICATION_H_
