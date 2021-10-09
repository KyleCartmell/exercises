/**
 * @file
 * a minimal filter that doesn't actually do anything
*/

#include "libavutil/avstring.h"
#include "libavutil/eval.h"
#include "libavutil/opt.h"
#include "libavutil/intreadwrite.h"
#include "libavutil/parseutils.h"
#include "libavutil/pixdesc.h"

#include "avfilter.h"
#include "drawutils.h"
#include "internal.h"
#include "video.h"

#include <float.h>

typedef struct NoopContext {
    const AVClass *class;
} NoopContext;

static const AVOption noop_options[] = {
    { NULL }
};

AVFILTER_DEFINE_CLASS(noop);

static av_cold int init(AVFilterContext *ctx)
{
    NoopContext *noop = ctx->priv;
    return 0;
}

static av_cold void uninit(AVFilterContext *ctx)
{
    NoopContext *noop = ctx->priv;
}

static const enum AVPixelFormat pix_fmts[] = {
    AV_PIX_FMT_GBRP,   AV_PIX_FMT_GBRAP,
    AV_PIX_FMT_ARGB,   AV_PIX_FMT_RGBA,
    AV_PIX_FMT_ABGR,   AV_PIX_FMT_BGRA,
    AV_PIX_FMT_0RGB,   AV_PIX_FMT_RGB0,
    AV_PIX_FMT_0BGR,   AV_PIX_FMT_BGR0,
    AV_PIX_FMT_RGB24,  AV_PIX_FMT_BGR24,
    AV_PIX_FMT_GRAY8,
    AV_PIX_FMT_YUV410P,
    AV_PIX_FMT_YUV444P,  AV_PIX_FMT_YUVJ444P,
    AV_PIX_FMT_YUV420P,  AV_PIX_FMT_YUVJ420P,
    AV_PIX_FMT_YUVA444P, AV_PIX_FMT_YUVA420P,
    AV_PIX_FMT_YUV420P10LE, AV_PIX_FMT_YUVA420P10LE,
    AV_PIX_FMT_YUV444P10LE, AV_PIX_FMT_YUVA444P10LE,
    AV_PIX_FMT_YUV420P12LE,
    AV_PIX_FMT_YUV444P12LE,
    AV_PIX_FMT_YUV444P16LE, AV_PIX_FMT_YUVA444P16LE,
    AV_PIX_FMT_YUV420P16LE, AV_PIX_FMT_YUVA420P16LE,
    AV_PIX_FMT_YUV444P9LE, AV_PIX_FMT_YUVA444P9LE,
    AV_PIX_FMT_YUV420P9LE, AV_PIX_FMT_YUVA420P9LE,
    AV_PIX_FMT_NONE
};

static int config_props(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    NoopContext *noop = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];
    return 0;
}

static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out;
    NoopContext *noop = ctx->priv;
    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(out, in);
    int ret = ff_filter_frame(outlink, in);
    return ret;
}

static int process_command(AVFilterContext *ctx, const char *cmd, const char *args,
                           char *res, int res_len, int flags)
{
    NoopContext *noop = ctx->priv;
    return 0;
}

static const AVFilterPad noop_inputs[] = {
    {
        .name         = "default",
        .type         = AVMEDIA_TYPE_VIDEO,
        .filter_frame = filter_frame,
    },
};

static const AVFilterPad noop_outputs[] = {
    {
        .name         = "default",
        .type         = AVMEDIA_TYPE_VIDEO,
        .config_props = config_props,
    },
};

const AVFilter ff_vf_noop = {
    .name          = "noop",
    .description   = NULL_IF_CONFIG_SMALL("It does nothing."),
    .priv_size     = sizeof(NoopContext),
    .init          = init,
    .uninit        = uninit,
    .process_command = process_command,
    FILTER_INPUTS(noop_inputs),
    FILTER_OUTPUTS(noop_outputs),
    FILTER_PIXFMTS_ARRAY(pix_fmts),
    .priv_class    = &noop_class,
    .flags         = 0,
};

