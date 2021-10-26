# include "RubikProgram.hpp"

RubikProgram::RubikProgram(int ac, char **av) {
    RubikProgramOptions options;

    options.moves.clear();

    if (parsing(ac, av, options))
        return ;
    if (options.visu)
    {
        v = new Visualizer(1080, 1080);
        v->draw();
    }


    if (!options.moves.empty() || options.shuffle)
    {
        if (options.shuffle)
            options.moves = c.shuffle(options.shuffleIterations);
        else
            for (auto& m: options.moves)
                c.move(m);
        printf("MIX (%lu) : ", options.moves.size());
        for (auto& m: options.moves)
        {
            printf("%s ", m.c_str());
            if (options.visu)
                v->moveQueue.emplace(m);
        }
        printf("\n");
        if (options.visu)
            v->drawLoop();

        std::vector<std::string> solPath = k.solve(c);
        printf("SOL (%lu) : ", solPath.size());
        for (auto& m: solPath)
        {
            printf("%s ", m.c_str());
            if (options.visu)
                v->moveQueue.emplace(m);
        }
        printf("\n");
        if (options.visu)
            v->drawLoop();
    }
}

RubikProgram::~RubikProgram(){
    if (v)
        delete(v);
}