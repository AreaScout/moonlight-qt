#pragma once

#include "renderer.h"

#include <xf86drm.h>
#include <xf86drmMode.h>
#include <sys/ioctl.h>

extern "C" {
    #include <rga/RgaApi.h>
}

class DrmRenderer : public IFFmpegRenderer {
public:
    DrmRenderer();
    virtual ~DrmRenderer() override;
    virtual bool initialize(PDECODER_PARAMETERS params) override;
    virtual bool prepareDecoderContext(AVCodecContext* context, AVDictionary** options) override;
    virtual void renderFrame(AVFrame* frame) override;
    virtual enum AVPixelFormat getPreferredPixelFormat(int videoFormat) override;
    virtual int getRendererAttributes() override;
    void initRotateBuffer(int frameWidth, int frameHeight, uint32_t format);

private:
    int m_DrmFd;
    int m_RotPrimeFd;
    uint32_t m_CrtcId;
    uint32_t m_PlaneId;
    uint32_t m_CurrentFbId;
    SDL_Rect m_OutputRect;
    rga_info_t src_info;
    rga_info_t dst_info;
};

