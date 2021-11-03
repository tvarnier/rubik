#include "Kociemba.hpp"

int Kociemba::Solver::minSol = 100;
int Kociemba::Solver::firstSol = 100;
std::vector<std::string> Kociemba::Solver::solPath = {};

size_t  hashPath(std::vector<int> path)
{
    size_t seed(0);
    std::hash<int>  hasher;

    for (const auto& move: path)
    {
        seed ^= hasher(move) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

int     pruneDiff(uint8_t currentDepht, uint8_t newDepht)
{
    if (currentDepht == 1 && newDepht == 3)
        return -1;
    else if (currentDepht == 3 && newDepht == 1)
        return +1;
    else
        return (newDepht - currentDepht);
}

bool     Kociemba::Solver::isStateUseless(const short& phase, const unsigned int& size, const P1& phase1, const P2& phase2)
{
    if (
        (phase == 1 && (unsigned int)(size + phase1.depht) > 12)
        || (phase == 1 && (unsigned int)(size + ((phase1.depht > phase2.cornPermDepht) ? phase1.depht : phase2.cornPermDepht)) >= minSol)
        || (phase == 2 && (unsigned int)(size + phase2.depht) >= minSol)
    )
        return (true);
    return (false);
}

std::string moveP1(int i)
{
    std::string moves[18] = {
        "U", "U2", "U'",
        "R", "R2", "R'",
        "F", "F2", "F'",
        "D", "D2", "D'",
        "L", "L2", "L'",
        "B", "B2", "B'"
    };
    return (moves[i]);
}

void    Kociemba::Solver::solveSucess(const Cube& rubik, SolvingState& solution)
{
    std::string moves[18] = {
        "U", "U2", "U'",
        "R", "R2", "R'",
        "F", "F2", "F'",
        "D", "D2", "D'",
        "L", "L2", "L'",
        "B", "B2", "B'"
    };

    if (firstSol == 100)
        firstSol = solution.path.size() ;

    if (solution.path.size() < minSol)
        minSol = solution.path.size();

    Cube tmp = rubik;

    solPath.clear();
    for (auto it = solution.path.begin(); it != solution.path.end(); ++it)
        solPath.emplace_back(moves[*it]);
}

size_t  Kociemba::Solver::getP1Length(unsigned int cornOrient, unsigned int flipUDSlice, uint8_t pruning)
{
    for (int moveId = 0; moveId < 18; ++moveId)
    {
        unsigned int newCornOrient = MoveTable::CornerOrientation[cornOrient][moveId];
        unsigned int newFlipUDSlice = MoveTable::FlipUDSlice[flipUDSlice][moveId];

        unsigned int newRep = Sym::RepTable::FlipUDSlice[newFlipUDSlice].first;
        unsigned int newSym = Sym::RepTable::FlipUDSlice[newFlipUDSlice].second[0];

        unsigned int newCornOrientSym = Sym::MoveTable::cornerOrientation[newCornOrient][newSym];

        unsigned int newPruning = PruneTable::Get::value_P1(newRep  * 2187 + newCornOrientSym);

        if (pruneDiff(pruning, newPruning) == -1)
            return (getP1Length(newCornOrient, newFlipUDSlice, newPruning) + 1);
    }
    return (0);
}

size_t  Kociemba::Solver::getP2Length(unsigned int cornPerm, unsigned int edgePerm, uint8_t pruning)
{
    for (int moveId = 0; moveId < 18; ++moveId)
    {
        if (moveId / 3 != ROT_UP && moveId / 3 != ROT_DOWN && moveId % 3 != 1 )
            continue ;
        unsigned int newCornPerm = MoveTable::CornerPermutation[cornPerm][moveId];
        unsigned int newEdgePerm = MoveTable::P2EdgePermutation[edgePerm][moveId];

        unsigned int newRep = Sym::RepTable::cornerPermutation[newCornPerm].first;
        unsigned int newSym = Sym::RepTable::cornerPermutation[newCornPerm].second[0];

        unsigned int newEdgePermSym = Sym::MoveTable::P2EdgePermutation[newEdgePerm][newSym];

        unsigned int newPruning = PruneTable::Get::value_P2_CPEP(newEdgePermSym  * 2768  + newRep);

        if (pruneDiff(pruning, newPruning) == -1)
            return (getP2Length(newCornPerm, newEdgePerm, newPruning) + 1);
    }
    return (0);
}

void    Kociemba::Solver::generateChilds(std::set<SolvingState>& open, std::unordered_set<size_t>& close, SolvingState& current, const Cube& rubik)
{
    for (int moveId = 0; moveId < 18; ++moveId)
    {
        if ((current.lastMove != -1 && moveId / 3 == current.lastMove / 3) ||
            (current.phase == 2 && moveId / 3 != ROT_UP && moveId / 3 != ROT_DOWN && moveId % 3 != 1 ))
            continue ;
        struct P1 phase1 = current.p1;
        struct P2 phase2 = current.p2;
        short phase = current.phase;
        int newDepht = current.depht;

        if (phase == 1)
        {
            unsigned int newCornOrient = MoveTable::CornerOrientation[phase1.cornOrient][moveId];
            unsigned int newFlipUDSlice = MoveTable::FlipUDSlice[phase1.flipUDSlice][moveId];

            unsigned int newRep = Sym::RepTable::FlipUDSlice[newFlipUDSlice].first;
            unsigned int newSym = Sym::RepTable::FlipUDSlice[newFlipUDSlice].second[0];

            unsigned int newCornOrientSym = Sym::MoveTable::cornerOrientation[newCornOrient][newSym];

            int pruneDiffP1(pruneDiff(phase1.pruning, PruneTable::Get::value_P1(newRep  * 2187 + newCornOrientSym)));
            
            newDepht += (pruneDiffP1 * 2);
            phase1.depht += pruneDiffP1;

            phase1.cornOrient = newCornOrient;
            phase1.flipUDSlice = newFlipUDSlice;
            phase1.pruning = PruneTable::Get::value_P1(newRep  * 2187 + newCornOrientSym);

            phase1.UDSliceSorted = MoveTable::UDSliceSorted[phase1.UDSliceSorted][moveId];
            phase1.RLSliceSorted = MoveTable::RLSliceSorted[phase1.RLSliceSorted][moveId];
            phase1.FBSliceSorted = MoveTable::FBSliceSorted[phase1.FBSliceSorted][moveId];

            phase2.cornPerm = MoveTable::CornerPermutation[phase2.cornPerm][moveId];
            phase2.cornPermDepht = DephtTable::CornerPermutation[phase2.cornPerm];

            if (newFlipUDSlice == 0 && newCornOrient == 0)
            {
                phase = 2;
                phase2.edgePerm = MoveTable::edge8Perm[phase1.RLSliceSorted][phase1.FBSliceSorted % 24];
                phase2.UDSlice = phase1.UDSliceSorted % 24;
                phase2.CPEP = PruneTable::Get::value_P2_CPEP( Sym::MoveTable::P2EdgePermutation[phase2.edgePerm][Sym::RepTable::cornerPermutation[phase2.cornPerm].second[0]] * 2768 + 
                                                            Sym::RepTable::cornerPermutation[phase2.cornPerm].first );

                phase2.depht = getP2Length(phase2.cornPerm, phase2.edgePerm, phase2.CPEP);
            }
        }
        else if (phase == 2)
        {
            unsigned int newCornPerm = MoveTable::CornerPermutation[phase2.cornPerm][moveId];
            unsigned int newEdgePerm = MoveTable::P2EdgePermutation[phase2.edgePerm][moveId];
            unsigned int newP2UDSlice = MoveTable::P2UDSlice[phase2.UDSlice][moveId];

            unsigned int newRep = Sym::RepTable::cornerPermutation[newCornPerm].first;
            unsigned int newSym = Sym::RepTable::cornerPermutation[newCornPerm].second[0];

            unsigned int newEdgePermSym = Sym::MoveTable::P2EdgePermutation[newEdgePerm][newSym];

            unsigned int newCPEP = PruneTable::Get::value_P2_CPEP(newEdgePermSym  * 2768  + newRep);

            unsigned int pruneDiffP2 = pruneDiff(phase2.CPEP, newCPEP);
            
            newDepht += (pruneDiffP2 * 2);
            phase2.depht += pruneDiffP2;
        
            phase2.cornPerm = newCornPerm;
            phase2.edgePerm = newEdgePerm;
            phase2.UDSlice = newP2UDSlice;
            phase2.CPEP = newCPEP;
        }

        if ( isStateUseless(phase, current.path.size() + 1, phase1, phase2) )
            continue ;
        
        std::vector<int> newPath = current.path;
        newPath.push_back(moveId);
        size_t newIndex = hashPath(newPath);

        
        if (close.find( newIndex ) == close.end())
        {
            close.insert( newIndex );
            open.emplace(phase1, phase2, phase, newDepht + 1, newPath, newIndex, moveId);
        }
    }
}

void    Kociemba::Solver::solveLoop(Cube& rubik)
{
    std::set<SolvingState>  open;
    std::unordered_set<size_t>  close;

    unsigned int cornOrient = Coord::cornerOrientation(rubik.m_corners.o);
    unsigned int EdgeOrient = Coord::edgeOrientation(rubik.m_edges.o);
    unsigned int UDSlice = Coord::UDSlice(rubik.m_edges.p);
    unsigned int flipUDSlice = EdgeOrient * UD_SLICE_MOVETABLE_SIZE + UDSlice;

    unsigned int cornPerm = Coord::cornerPermutation(rubik.m_corners.p);
    unsigned int edgePerm = Coord::P2EdgePermutation(rubik.m_edges.p);
    unsigned int P2UDSlice = Coord::P2UDSlice(rubik.m_edges.p);

    unsigned int P1Pruning = PruneTable::Get::value_P1(Sym::RepTable::FlipUDSlice[flipUDSlice].first * CORNER_ORIENTATION_MOVETABLE_SIZE
                                    + Sym::MoveTable::cornerOrientation[cornOrient][Sym::RepTable::FlipUDSlice[flipUDSlice].second[0]]);
    unsigned int P2_CPEP_Pruning = PruneTable::Get::value_P2_CPEP(Sym::MoveTable::P2EdgePermutation[edgePerm][Sym::RepTable::cornerPermutation[cornPerm].second[0]] * 2768
                                            + Sym::RepTable::cornerPermutation[cornPerm].first);

    short phase(1);
    if (cornOrient == 0 && flipUDSlice == 0)
        phase = 2;

    open.emplace(
        P1(
            cornOrient,
            flipUDSlice,
            Coord::UDSliceSorted(rubik.m_edges.p),
            Coord::RLSliceSorted(rubik.m_edges.p),
            Coord::FBSliceSorted(rubik.m_edges.p),
            P1Pruning,
            Solver::getP1Length(cornOrient, flipUDSlice, P1Pruning)
        ),
        P2(
            cornPerm,
            edgePerm,
            P2UDSlice,
            P2_CPEP_Pruning,
            Solver::getP2Length(cornPerm, edgePerm, P2_CPEP_Pruning),
            DephtTable::CornerPermutation[cornPerm]
        ),
        phase
    );
    close.emplace( hashPath(open.begin()->path) );

    size_t  opened = 0;

    auto overMinSol = [](auto const& x) {
       return( Solver::isStateUseless(x.phase, x.path.size(), x.p1, x.p2) );
    };

    while (!open.empty())
    {
        SolvingState current = *(open.begin());
        open.erase(open.begin());

        /* ===== DEBUG ===== */
        if (minSol <= current.path.size())
            continue ;

        if (current.phase == 2 && current.p2.cornPerm == 0 && current.p2.edgePerm == 0 && current.p2.UDSlice == 0)
        {
            Solver::solveSucess(rubik, current);
            std::erase_if(open,overMinSol);
        }
        else
            Solver::generateChilds(open, close, current, rubik);
    }
}

std::vector<std::string>    Kociemba::solve(Cube& rubik)
{
    Solver::solPath.clear();
    Solver::minSol = 100;
    Solver::firstSol = 100;

    Solver::solveLoop(rubik);

    for (auto m : Solver::solPath)
        rubik.move(m);

    return (Solver::solPath);
}