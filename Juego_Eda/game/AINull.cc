#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Null


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
  void bfs_all(Unit u) {
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
            while(path[next.i][next.j].first != u.pos) next = path[next.i][next.j].first; //Backtracking till first move to set objective.
            //cerr << "I am at: " << u.pos.i << " " << u.pos.j << endl;
            //cerr << "Finished backtracking: " << next.i << " " << next.j << endl;
            move(u.id, path[next.i][next.j].second);
            return;
          }
        }
      }
    }
  }

  void move_units(Unit un) {
    //cerr << "Moving. Unit at: " << un.pos.i << " " << un.pos.j << endl;
    bfs_all(un);
    //cerr << "Unit finished moving: " << un.id << endl;
  }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    //vector<vector<int>> posmap = mapa_posiciones();
    //map_print(posmap);
    vector<int> my_units = alive_units(me());
    for (int k = 0; k < my_units.size(); ++k) {
      Unit un = unit(my_units[k]);
      move_units(un);
    }
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
