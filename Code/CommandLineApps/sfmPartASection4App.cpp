/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Social Force Model

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

  Author: John Duffy

=============================================================================*/

#include <sfmExceptionMacro.h>
#include <sfmTypes.h>
#include <sfmPedestrian.h>
#include <sfmForces.h>

#include <iostream>
#include <vector>


int main(int argc, char** argv)
{
  // Create a vector of pedestrians.
  std::vector<sfm::Pedestrian> ps;
  double desired_speed {1.3};
  double relaxation_time {0.5};
  ps.push_back(sfm::Pedestrian(sfm::Pos2d(0.0, 1.0), sfm::Pos2d(POS2D_XWRAP, 1.0), desired_speed, relaxation_time));
  ps.push_back(sfm::Pedestrian(sfm::Pos2d(0.0, 9.0), sfm::Pos2d(POS2D_XWRAP, 9.0), desired_speed, relaxation_time));
  ps.push_back(sfm::Pedestrian(sfm::Pos2d(POS2D_XWRAP, 4.9), sfm::Pos2d(0.0, 4.9), desired_speed, relaxation_time));
  ps.push_back(sfm::Pedestrian(sfm::Pos2d(0.0, 5.1), sfm::Pos2d(POS2D_XWRAP, 5.1), desired_speed, relaxation_time));

  // Print velocities and positions at t = 0.0.
  std::cout << 0.0;
  for (auto &p : ps) {
    std::cout << " " << p.GetVelocity().GetXLength() << " " << p.GetVelocity().GetYLength();
    std::cout << " " << p.GetPosition().GetX() << " " << p.GetPosition().GetY();
  }
  std::cout << std::endl;

  // Time loop.
  double finish_time_s {50.0};
  double dt {0.25};
  for (auto t = dt; t < finish_time_s + dt; t += dt) {
    std::cout << t;
    // Pedestrians loop.
    for (auto i = 0; i < ps.size(); ++i) { // Need index i!
      // Create a vector of other pedestrians.
      std::vector<sfm::Pedestrian> other_ps = ps;
      other_ps.erase(other_ps.begin() + i);
      // Update each pedestrian's velocity.
      ps[i].SetVelocity(ps[i].GetVelocity() + (sfm::ResultantForce(ps[i], other_ps, dt) * dt));
      // Update each pedestrian's position.
      ps[i].SetPosition(ps[i].GetPosition() + (ps[i].GetVelocity() * dt));
      // Print updated velocities and positions at time t.
      std::cout << " " << ps[i].GetVelocity().GetXLength() << " " << ps[i].GetVelocity().GetYLength();
      std::cout << " " << ps[i].GetPosition().GetX() << " " << ps[i].GetPosition().GetY();
    }
    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}