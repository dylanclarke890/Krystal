#pragma once

#include "Graphics/Colour.hpp"
#include "Graphics/Colours.hpp"
#include "Graphics/Materials/PhongMaterialDescriptor.hpp"

// Name	Ambient	Diffuse	Specular	Shininess
// emerald	0.0215	0.1745	0.0215	0.07568	0.61424	0.07568	0.633	0.727811	0.633	0.6
// jade	0.135	0.2225	0.1575	0.54	0.89	0.63	0.316228	0.316228	0.316228	0.1
// obsidian	0.05375	0.05	0.06625	0.18275	0.17	0.22525	0.332741	0.328634	0.346435	0.3
// pearl	0.25	0.20725	0.20725	1	0.829	0.829	0.296648	0.296648	0.296648	0.088
// ruby	0.1745	0.01175	0.01175	0.61424	0.04136	0.04136	0.727811	0.626959	0.626959	0.6
// turquoise	0.1	0.18725	0.1745	0.396	0.74151	0.69102	0.297254	0.30829	0.306678	0.1
// brass	0.329412	0.223529	0.027451	0.780392	0.568627	0.113725	0.992157	0.941176	0.807843	0.21794872
// bronze	0.2125	0.1275	0.054	0.714	0.4284	0.18144	0.393548	0.271906	0.166721	0.2
// chrome	0.25	0.25	0.25	0.4	0.4	0.4	0.774597	0.774597	0.774597	0.6
// copper	0.19125	0.0735	0.0225	0.7038	0.27048	0.0828	0.256777	0.137622	0.086014	0.1
// gold	0.24725	0.1995	0.0745	0.75164	0.60648	0.22648	0.628281	0.555802	0.366065	0.4
// silver	0.19225	0.19225	0.19225	0.50754	0.50754	0.50754	0.508273	0.508273	0.508273	0.4
// black plastic	0.0	0.0	0.0	0.01	0.01	0.01	0.50	0.50	0.50	.25
// cyan plastic	0.0	0.1	0.06	0.0	0.50980392	0.50980392	0.50196078	0.50196078	0.50196078	.25
// green plastic	0.0	0.0	0.0	0.1	0.35	0.1	0.45	0.55	0.45	.25
// red plastic	0.0	0.0	0.0	0.5	0.0	0.0	0.7	0.6	0.6	.25
// white plastic	0.0	0.0	0.0	0.55	0.55	0.55	0.70	0.70	0.70	.25
// yellow plastic	0.0	0.0	0.0	0.5	0.5	0.0	0.60	0.60	0.50	.25
// black rubber	0.02	0.02	0.02	0.01	0.01	0.01	0.4	0.4	0.4	.078125
// cyan rubber	0.0	0.05	0.05	0.4	0.5	0.5	0.04	0.7	0.7	.078125
// green rubber	0.0	0.05	0.0	0.4	0.5	0.4	0.04	0.7	0.04	.078125
// red rubber	0.05	0.0	0.0	0.5	0.4	0.4	0.7	0.04	0.04	.078125
// white rubber	0.05	0.05	0.05	0.5	0.5	0.5	0.7	0.7	0.7	.078125
// yellow rubber	0.05	0.05	0.0	0.5	0.5	0.4	0.7	0.7	0.04	.078125

namespace Krys::Gfx::PhongMaterials
{
  using descriptor_t = PhongMaterialDescriptor;

  constexpr static descriptor_t Emerald {.Ambient = Colour {0.0215f, 0.1745f, 0.0215f},
                                         .Diffuse = Colour {0.07568f, 0.61424f, 0.07568f},
                                         .Specular = Colour {0.633f, 0.727811f, 0.633f},
                                         .Shininess = 0.6f * 128};

  constexpr static descriptor_t Jade {.Ambient = Colour {0.135f, 0.2225f, 0.1575f},
                                      .Diffuse = Colour {0.54f, 0.89f, 0.63f},
                                      .Specular = Colour {0.316228f, 0.316228f, 0.316228f},
                                      .Shininess = 0.1f * 128};

  constexpr static descriptor_t Obsidian {.Ambient = Colour {0.05375f, 0.05f, 0.06625f},
                                          .Diffuse = Colour {0.18275f, 0.17f, 0.22525f},
                                          .Specular = Colour {0.332741f, 0.328634f, 0.346435f},
                                          .Shininess = 0.3f * 128};

  constexpr static descriptor_t Pearl {.Ambient = Colour {0.25f, 0.20725f, 0.20725f},
                                       .Diffuse = Colour {1.0f, 0.829f, 0.829f},
                                       .Specular = Colour {0.296648f, 0.296648f, 0.296648f},
                                       .Shininess = 0.088f * 128};

  constexpr static descriptor_t Ruby {.Ambient = Colour {0.1745f, 0.01175f, 0.01175f},
                                      .Diffuse = Colour {0.61424f, 0.04136f, 0.04136f},
                                      .Specular = Colour {0.727811f, 0.626959f, 0.626959f},
                                      .Shininess = 0.6f * 128};

  constexpr static descriptor_t Turquoise {.Ambient = Colour {0.1f, 0.18725f, 0.1745f},
                                           .Diffuse = Colour {0.396f, 0.74151f, 0.69102f},
                                           .Specular = Colour {0.297254f, 0.30829f, 0.306678f},
                                           .Shininess = 0.1f * 128};

  constexpr static descriptor_t Brass {.Ambient = Colour {0.329412f, 0.223529f, 0.027451f},
                                       .Diffuse = Colour {0.780392f, 0.568627f, 0.113725f},
                                       .Specular = Colour {0.992157f, 0.941176f, 0.807843f},
                                       .Shininess = 0.21794872f * 128};

  constexpr static descriptor_t Bronze {.Ambient = Colour {0.2125f, 0.1275f, 0.054f},
                                        .Diffuse = Colour {0.714f, 0.4284f, 0.18144f},
                                        .Specular = Colour {0.393548f, 0.271906f, 0.166721f},
                                        .Shininess = 0.2f * 128};

  constexpr static descriptor_t Chrome {.Ambient = Colour {0.25f, 0.25f, 0.25f},
                                        .Diffuse = Colour {0.4f, 0.4f, 0.4f},
                                        .Specular = Colour {0.774597f, 0.774597f, 0.774597f},
                                        .Shininess = 0.6f * 128};

  constexpr static descriptor_t Copper {.Ambient = Colour {0.19125f, 0.0735f, 0.0225f},
                                        .Diffuse = Colour {0.7038f, 0.27048f, 0.0828f},
                                        .Specular = Colour {0.256777f, 0.137622f, 0.086014f},
                                        .Shininess = 0.1f * 128};

  constexpr static descriptor_t Gold {.Ambient = Colour {0.24725f, 0.1995f, 0.0745f},
                                      .Diffuse = Colour {0.75164f, 0.60648f, 0.22648f},
                                      .Specular = Colour {0.628281f, 0.555802f, 0.366065f},
                                      .Shininess = 0.4f * 128};

  constexpr static descriptor_t Silver {.Ambient = Colour {0.19225f, 0.19225f, 0.19225f},
                                        .Diffuse = Colour {0.50754f, 0.50754f, 0.50754f},
                                        .Specular = Colour {0.508273f, 0.508273f, 0.508273f},
                                        .Shininess = 0.4f * 128};

  constexpr static descriptor_t BlackPlastic {.Ambient = Colour {0.0f, 0.0f, 0.0f},
                                              .Diffuse = Colour {0.01f, 0.01f, 0.01f},
                                              .Specular = Colour {0.50f, 0.50f, 0.50f},
                                              .Shininess = 0.25f * 128};

  constexpr static descriptor_t CyanPlastic {.Ambient = Colour {0.0f, 0.1f, 0.06f},
                                             .Diffuse = Colour {0.0f, 0.50980392f, 0.50980392f},
                                             .Specular = Colour {0.50196078f, 0.50196078f, 0.50196078f},
                                             .Shininess = 0.25f * 128};

  constexpr static descriptor_t GreenPlastic {.Ambient = Colour {0.0f, 0.0f, 0.0f},
                                              .Diffuse = Colour {0.1f, 0.35f, 0.1f},
                                              .Specular = Colour {0.45f, 0.55f, 0.45f},
                                              .Shininess = 0.25f * 128};

  constexpr static descriptor_t RedPlastic {.Ambient = Colour {0.0f, 0.0f, 0.0f},
                                            .Diffuse = Colour {0.5f, 0.0f, 0.0f},
                                            .Specular = Colour {0.7f, 0.6f, 0.6f},
                                            .Shininess = 0.25f * 128};

  constexpr static descriptor_t WhitePlastic {.Ambient = Colour {0.0f, 0.0f, 0.0f},
                                              .Diffuse = Colour {0.55f, 0.55f, 0.55f},
                                              .Specular = Colour {0.70f, 0.70f, 0.70f},
                                              .Shininess = 0.25f * 128};

  constexpr static descriptor_t YellowPlastic {.Ambient = Colour {0.0f, 0.0f, 0.0f},
                                               .Diffuse = Colour {0.5f, 0.5f, 0.0f},
                                               .Specular = Colour {0.60f, 0.60f, 0.50f},
                                               .Shininess = 0.25f * 128};

  constexpr static descriptor_t BlackRubber {.Ambient = Colour {0.02f, 0.02f, 0.02f},
                                             .Diffuse = Colour {0.01f, 0.01f, 0.01f},
                                             .Specular = Colour {0.4f, 0.4f, 0.4f},
                                             .Shininess = 0.078125f * 128};

  constexpr static descriptor_t CyanRubber {.Ambient = Colour {0.0f, 0.05f, 0.05f},
                                            .Diffuse = Colour {0.4f, 0.5f, 0.5f},
                                            .Specular = Colour {0.04f, 0.7f, 0.7f},
                                            .Shininess = 0.078125f * 128};

  constexpr static descriptor_t GreenRubber {.Ambient = Colour {0.0f, 0.05f, 0.0f},
                                             .Diffuse = Colour {0.4f, 0.5f, 0.4f},
                                             .Specular = Colour {0.04f, 0.7f, 0.04f},
                                             .Shininess = 0.078125f * 128};

  constexpr static descriptor_t RedRubber {.Ambient = Colour {0.05f, 0.0f, 0.0f},
                                           .Diffuse = Colour {0.5f, 0.4f, 0.4f},
                                           .Specular = Colour {0.7f, 0.04f, 0.04f},
                                           .Shininess = 0.078125f * 128};

  constexpr static descriptor_t WhiteRubber {.Ambient = Colour {0.05f, 0.05f, 0.05f},
                                             .Diffuse = Colour {0.5f, 0.5f, 0.5f},
                                             .Specular = Colour {0.7f, 0.7f, 0.7f},
                                             .Shininess = 0.078125f * 128};

  constexpr static descriptor_t YellowRubber {.Ambient = Colour {0.05f, 0.05f, 0.0f},
                                              .Diffuse = Colour {0.5f, 0.5f, 0.4f},
                                              .Specular = Colour {0.7f, 0.7f, 0.04f},
                                              .Shininess = 0.078125f * 128};
}