/*
 * service_test.cpp
 *
 *  Created on: May 10, 2017
 *      Author: c_akong
 */


#include "binder_test.h"
using namespace android;


int main(int argc, char *argv[])
{
    sp<ProcessState> proc(ProcessState::self());
    //get service manager
    sp<IServiceManager> sm = defaultServiceManager();

    sm->addService(String16("service.testmanager"),new Test());
ALOGE("bindertest service is starting.....");
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();

    return 0;
}
