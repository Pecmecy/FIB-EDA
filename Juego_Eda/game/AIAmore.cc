#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Amore


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  struct Movimientos {
    Dir direccion;
    int prioridad;
    int id;
  };

  const vector<Dir> dirs = {Up,Down,Left,Right};
  typedef vector<vector<Dir>> Board;

  /**
  * Map with the resources on the board.
  */
  vector<vector<int> > mapa_posiciones() {
        vector<vector<int> > posiciones(board_rows(), vector<int> (board_cols()));
        for (int i = 0; i < board_rows(); ++i) {
            for (int j = 0; j < board_cols(); ++j) {
                Pos p (i, j);
                if (cell(p).type == Waste) posiciones[i][j] = -2; // There is waste.
                else if (cell(p).id != -1 and unit(cell(p).id).player != me()) posiciones[i][j] = 77;  // There is a unit which is not mine.
                else if (cell(p).id != -1 and unit(cell(p).id).player == me()) posiciones[i][j] = 69;  // There is a unit which is mine.
                else if (cell(p).food) posiciones[i][j] = 22;     // There is food.
                else posiciones[i][j] = -3;                       
            }
        }
    return posiciones;
  }

  /**
  * Map writing.
  */
  void map_print(const vector<vector<int>>& m) {
    for (int i = 0; i < m.size(); ++i) {
      for (int j = 0; j < m[0].size(); ++j) {
        cerr << m[i][j]; 
      }
      cerr << endl;
    }
 }

 /**
  * BFS to look for the closest food.
 */
  void bfs_all(Unit u, vector<Movimientos> &mmov) {
    pair<Pos, Dir> initial = make_pair(Pos(-1,-1), Down);
    vector<vector<pair<Pos, Dir>>> path(60, vector<pair<Pos, Dir>>(60, initial));
    vector<vector<bool>> visited(60, vector<bool>(60, false));
    queue<Pos> q;
    q.push(u.pos);
    visited[u.pos.i][u.pos.j] = true;
    while(!q.empty()) {
      Pos ant = q.front();
      q.pop();
      for(int k = 0; k < 4; ++k) {
        Pos next = ant + dirs[k];
        if(pos_ok(next) and !visited[next.i][next.j] and cell(next).type != Waste) {
          visited[next.i][next.j] = true;
          q.push(next);
          path[next.i][next.j] = make_pair(ant, dirs[k]);
          //cerr << "DEBUGGING " << next.i << " " << next.j << endl;
          if(cell(next).food or (cell(next).id != -1 and unit(cell(next).id).player != me() and unit(cell(next).id).type != 1) or (cell(next).id != -1 and unit(cell(next).id).type == 2)) {  //Whatever it finds go for it as priority.
            //cerr << "Found food at: " << next.i << " " << next.j << endl;
            Pos aux = next;
            while(path[next.i][next.j].first != u.pos)  {
                next = path[next.i][next.j].first; //Backtracking till first move to set objective.
            }
            //cerr << "I am at: " << u.pos.i << " " << u.pos.j << endl;
            //cerr << "Finished backtracking: " << next.i << " " << next.j << endl;
            Movimientos movprio;
            if (cell(next).id != -1 and unit(cell(next).id).player != me() and unit(cell(next).id).type != 1) {movprio = {path[next.i][next.j].second, 5, u.id};}
            else movprio = {path[next.i][next.j].second, 0, u.id};
            mmov.push_back(movprio);
            return;
          }
        }
      }
    }
  }

  bool zombie_diagonal(Pos next, Pos &zpos) {
    for (int i = -1; i < 2; i+=2) { 
        for (int j = -1; j < 2; j+=2) {
            zpos = next + Pos(i, j);
            if (pos_ok(zpos) and cell(zpos).id != -1 and unit(cell(zpos).id).type == Zombie) {
                cerr << "zpos: " << zpos << " upos: " << next << endl;
                return true;
            }
        }
    }
    return false;
  }
    
  bool zombie_near(Unit un) {
    for (int i = -2; i < 3; i+=4) { 
        for (int j = -1; j < 1; ++j) {
            Pos p = un.pos + Pos(i, j); //Pos(5,7) -> Pos(3,5) -> Pos(3,6) 
            if (pos_ok(p) and cell(p).id != -1 and unit(cell(p).id).type == Zombie) return true;
        }
    }
    for (int j = -2; j < 3; j+=4) { 
        for (int i = -1; i < 1; ++i) {
            Pos p = un.pos + Pos(i, j); //Pos(5,7) -> Pos(3,5) -> Pos(3,6) 
            if (pos_ok(p) and cell(p).id != -1 and unit(cell(p).id).type == Zombie) return true;
        }
    }
    return false;
  }

  void move_units(Unit un, vector<Movimientos> &mmov) {
    //cerr << "Moving. Unit at: " << un.pos.i << " " << un.pos.j << endl;
    Pos zpos;
    if ((!zombie_near(un) and !zombie_diagonal(un.pos, zpos)) or un.rounds_for_zombie != -1) bfs_all(un, mmov);
    else if (!zombie_diagonal(un.pos, zpos) and zombie_near(un)) {}
    else {
        if (zpos.i < un.pos.i and pos_ok(un.pos + Pos(1,0)) and cell(un.pos + Pos(1,0)).type != Waste) {move(un.id, Down); cerr << "Down" << endl;} 
        else if (zpos.i > un.pos.i and pos_ok(un.pos + Pos(-1,0))and cell(un.pos + Pos(-1,0)).type != Waste) {move(un.id, Up); cerr << "Up" << endl;}
        else if (zpos.j < un.pos.j and pos_ok(un.pos + Pos(0,1)) and cell(un.pos + Pos(0,1)).type != Waste) {move(un.id, Right); cerr << "Right" << endl;}
        else { move(un.id, Left); cerr << "Left" << endl;}
    }

    //cerr << "Unit finished moving: " << un.id << endl;
  }

    static bool cmp(const Movimientos& a, const Movimientos& b) {
        return a.prioridad > b.prioridad;
    }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    //vector<vector<int>> posmap = mapa_posiciones();
    //map_print(posmap);
    vector<int> my_units = alive_units(me());
    vector<Movimientos> my_moves;
    for (int k = 0; k < my_units.size(); ++k) {
      Unit un = unit(my_units[k]);
      move_units(un, my_moves);
    }
    sort(my_moves.begin(), my_moves.end(), cmp);
    for (int k = 0; k < my_moves.size(); ++ k) {
        move(my_moves[k].id, my_moves[k].direccion);
    }
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
