# include "RubikProgram.hpp"

void thread_func(Visualizer& visu)
{
    //printf("%x\n", v);
    visu.drawLoop();
}

RubikProgram::RubikProgram(int ac, char **av) {
    RubikProgramOptions options;

    std::printf("BEGIN\n");
    if (parsing(ac, av, options))
        return ;
    
    Visualizer visu(1080, 1080);

    visu.draw();

    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");
    visu.moveQueue.emplace("F");

    
    visu.drawLoop();

    //visu.drawLoop();

    //v = new Visualizer(1080, 1080);
    // v->draw();

    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");
    // v->moveQueue.emplace("F");

    // v->drawLoop();

    

    if (options.visu)
    {
        //v = std::make_shared<Visualizer>(1920, 1080);
        std::printf("   VISU\n");
        //v = new Visualizer(1920, 1080);
        visuThread = new std::thread(thread_func, std::ref(visu));
        visuThread->detach();
    }


    std::printf("WAIT ...\n");
    while (1);
    std::printf("END\n");
}