//
// Created by garwi on 10/29/2020.
//

#include <catch2/catch.hpp>
#include "gas_container.h"

namespace idealgas {
namespace container {

TEST_CASE("Wall collisions", "[wall][collision]") {
  Gas_container container(glm::vec2(0,0), 50);

  SECTION("horizontal collision with right wall") {
    container.Generate_particle(35, 25, 6, 0);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().x < 0); // particle is now moving in other direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 35); // particle is back to starting position after next frame
  }

  SECTION("horizontal collision with left wall") {
    container.Generate_particle(15, 25, -6, 0);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().x > 0); // particle is now moving in other direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 15); // particle is back to starting position after next frame
  }

  SECTION("vertical collision with bottom wall") {
    container.Generate_particle(25, 35, 0, 6);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y < 0); // particle is now moving in other direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 35); // particle is back to starting position after next frame
  }

  SECTION("vertical collision with top wall") {
    container.Generate_particle(25, 15, 0, -6);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y > 0); // particle is now moving in other direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 15); // particle is back to starting position after next frame
  }

  SECTION("Up and rightward collision with right wall") {
    container.Generate_particle(35, 20, 6, 5); // particle at (35,20) with velocity vect(6,5)
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().x < 0); // particle is now moving in opposite x direction, same y direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 30);
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 35);
  }

  SECTION("down and rightward collision with right wall") {
    container.Generate_particle(35, 30, 6, -5);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().x < 0);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 20); // particle is back to starting position after next frame
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 35); // particle is back to starting position after next frame
  }

  SECTION("Up and leftward collision with left wall") {
    container.Generate_particle(15, 20, -6, 5); // particle at (35,20) with velocity vect(6,5)
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().x > 0); // particle is now moving in opposite x direction, same y direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 30);
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 15);
  }

  SECTION("down and leftward collision with left wall") {
    container.Generate_particle(15, 30, -6, -5);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().x > 0);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 20); // particle is back to starting position after next frame
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 15); // particle is back to starting position after next frame
  }

  SECTION("Up and rightward collision with top wall") {
    container.Generate_particle(20, 15, 5, -6);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y > 0); // particle is now moving in opposite y direction, same y direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 15);
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 30);
  }

  SECTION("Up and leftward collision with top wall") {
    container.Generate_particle(30, 15, -5, -6);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y > 0);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 15); // particle is back to starting position after next frame
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 20); // particle is back to starting position after next frame
  }

  SECTION("Down and leftward collision with bottom wall") {
    container.Generate_particle(30, 35, -5, 6);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y < 0); // particle is now moving in opposite y direction, same y direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 35);
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 20);
  }

  SECTION("Down and rightward collision with bottom wall") {
    container.Generate_particle(20, 35, 5, 6);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y < 0);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 35); // particle is back to starting position after next frame
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 30); // particle is back to starting position after next frame
  }

}

} // namespace container

} // namespace idealgas

