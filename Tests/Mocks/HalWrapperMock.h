#ifndef __HALWRAPPERMOCK_H__
#define __HALWRAPPERMOCK_H__
#include "HalWrapper.h"
#include "gmock/gmock.h"

struct HalWrapperDummy : public HalWrapperInterface<HalWrapperDummy>
{

};

#endif

