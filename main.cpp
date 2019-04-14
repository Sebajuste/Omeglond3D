#include "CParallaxDemo.hpp"
#include "CTowerDemo.hpp"
#include "CShadowAreaDemo.hpp"
#include "CAnimatedModelDemo.hpp"
#include "CTestScene.hpp"

int main(int argc, char * argv[])
{


    IDemo * demo = new CParallaxDemo();
    //IDemo * demo = new CShadowAreaDemo();
    //IDemo * demo = new CAnimatedModelDemo();
    //IDemo * demo = new CTestScene();

    //demo->init();

    demo->start();

    delete demo;

    return 0;
}
