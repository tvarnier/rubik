#include "../Kociemba.hpp"

int     Kociemba::Sym::Rep::Generate::FlipUDSlice()
{
    std::filesystem::create_directories("./data");

    if (std::filesystem::exists("./data/flipUDSlice_Rep"))
    {
        std::ifstream file;
        file.open("./data/flipUDSlice_Rep");
        if (file.is_open())
        {
            file.seekg(0, std::ios::end);
            size_t l = file.tellg();
            file.seekg(0, std::ios::beg);
            if (l > 257720)
                l = 257720;
            file.read((char*)Sym::Rep::FlipUDSlice.data(), l);
            file.close();
        }
        else
        {
            std::cerr << "Error: Cannot Read File '" << "./data/flipUDSlice_Rep" << "'." << std::endl;
            return (1);
        }
    }
    else
    {
        std::ofstream file;
        file.open("./data/flipUDSlice_Rep");
        if (file.is_open())
        {
            std::cout << "Generating flipUDSlice Representants ..." << std::endl;

            ////////////////

            int repId(-1);

            for (unsigned int raw = 0; raw < FLIP_UD_SLICE_MOVETABLE_SIZE; ++raw)
            {
                struct edges Coord;
                Coord.o = Coord::Generate::edgeOrientation(raw / UD_SLICE_MOVETABLE_SIZE);
                Coord.p = Coord::Generate::UDSlice(raw % UD_SLICE_MOVETABLE_SIZE);

                int i(0);
                for (i = 0; i < 16; ++i)
                {
                    struct edges tmpCoord = Coord;
                    tmpCoord = Cube::multEdges(Cube::multEdges(Sym::Cubes[i].m_edges, tmpCoord), Sym::invCubes[i].m_edges);
                    unsigned int coord = Coord::edgeOrientation(tmpCoord.o) * UD_SLICE_MOVETABLE_SIZE + Coord::UDSlice(tmpCoord.p);
                    
                    if (coord < raw)
                        break ;
                }

                if (i == 16)
                    Sym::Rep::FlipUDSlice[++repId] = raw;
            }

            ////////////////

            if(!file.write((char*)Sym::Rep::FlipUDSlice.data(), 257720))
            {
                file.close();
                std::cerr << "Error: Failed to Write in File '" << "./data/flipUDSlice_Rep" << "'." << std::endl;
                return (1);
            }
            file.close();
        }
        else
        {
            std::cerr << "Error: Cannot Write File '" << "./data/flipUDSlice_Rep" << "'." << std::endl;
            return (1);
        }
    }
    return (0);
}

void    Kociemba::Sym::RepTable::Generate::FlipUDSlice()
{
    size_t repId(0);

    for (unsigned int raw = 0; raw < FLIP_UD_SLICE_MOVETABLE_SIZE && repId < 64430; ++raw)
    {
        if (raw == Sym::Rep::FlipUDSlice[repId])
        {
            struct edges Coord;
            Coord.o = Coord::Generate::edgeOrientation(raw / UD_SLICE_MOVETABLE_SIZE);
            Coord.p = Coord::Generate::UDSlice(raw % UD_SLICE_MOVETABLE_SIZE);

            for (int sym = 0; sym < 16; ++sym)
            {
                struct edges tmpCoord = Coord;

                tmpCoord = Cube::multEdges(Cube::multEdges(Sym::Cubes[sym].m_edges, tmpCoord), Sym::invCubes[sym].m_edges);

                unsigned int coord = Coord::edgeOrientation(tmpCoord.o) * UD_SLICE_MOVETABLE_SIZE + Coord::UDSlice(tmpCoord.p);                
                Sym::RepTable::FlipUDSlice[coord].first = repId;
                Sym::RepTable::FlipUDSlice[coord].second.push_back(sym);
            }
            repId++;
        }
    }
}