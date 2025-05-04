#include "OpenCLAdapter.h"


void OpenCLAdapter::getOpenCLParams(OpenCLParams& openclParams) {
    
    cl::Platform::get(&openclParams.platforms);
    openclParams.ret = openclParams.platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &openclParams.devices);
    openclParams.context = cl::Context(openclParams.devices);
    openclParams.queue = cl::CommandQueue(openclParams.context, openclParams.devices[0]);

}


void OpenCLAdapter::finishOpenCLParams(OpenCLParams& openclParams) {

    openclParams.queue.finish();

}
