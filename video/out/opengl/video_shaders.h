/*
 * This file is part of mpv.
 *
 * mpv is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * mpv is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with mpv.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MP_GL_VIDEO_SHADERS_H
#define MP_GL_VIDEO_SHADERS_H

#include <libavutil/lfg.h>

#include "common.h"
#include "utils.h"
#include "video.h"

extern const struct deband_opts deband_opts_def;
extern const struct m_sub_options deband_conf;

void sampler_prelude(struct gl_shader_cache *sc, int tex_num);
void pass_sample_separated_gen(struct gl_shader_cache *sc, struct scaler *scaler,
                               int d_x, int d_y);
void pass_sample_polar(struct gl_shader_cache *sc, struct scaler *scaler,
                       int components, int glsl_version);
void pass_compute_polar(struct gl_shader_cache *sc, struct scaler *scaler,
                        int components, int bw, int bh, float ratiox,
                        float ratioy);
void pass_sample_bicubic_fast(struct gl_shader_cache *sc);
void pass_sample_oversample(struct gl_shader_cache *sc, struct scaler *scaler,
                            int w, int h);

void pass_linearize(struct gl_shader_cache *sc, enum mp_csp_trc trc);
void pass_delinearize(struct gl_shader_cache *sc, enum mp_csp_trc trc);
void pass_ootf(struct gl_shader_cache *sc, enum mp_csp_light light, float peak);
void pass_inverse_ootf(struct gl_shader_cache *sc, enum mp_csp_light light, float peak);

void pass_color_map(struct gl_shader_cache *sc,
                    struct mp_colorspace src, struct mp_colorspace dst,
                    enum tone_mapping algo, float tone_mapping_param,
                    float tone_mapping_desat, bool use_detected_peak,
                    bool is_linear);

void pass_sample_deband(struct gl_shader_cache *sc, struct deband_opts *opts,
                        AVLFG *lfg);

void pass_sample_unsharp(struct gl_shader_cache *sc, float param);

#endif
