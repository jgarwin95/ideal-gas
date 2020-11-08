//
// Created by garwi on 10/29/2020.
//

#include <catch2/catch.hpp>
#include "gas_container.h"
#include "gas_histogram.h"

namespace idealgas {
namespace container {

TEST_CASE("Wall collisions", "[wall][collision]") {
  Gas_container container(glm::vec2(0,0), 50);

  SECTION("horizontal collision with right wall") {
    container.Generate_particle(35, 25, 6, 0, 10.0f, "red");
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().x < 0); // particle is now moving in other direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 35); // particle is back to starting position after next frame
  }

  SECTION("horizontal collision with left wall") {
    container.Generate_particle(15, 25, -6, 0, 10.0f, "red");
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().x > 0); // particle is now moving in other direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 15); // particle is back to starting position after next frame
  }

  SECTION("vertical collision with bottom wall") {
    container.Generate_particle(25, 35, 0, 6, 10.0f, "red");
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y < 0); // particle is now moving in other direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 35); // particle is back to starting position after next frame
  }

  SECTION("vertical collision with top wall") {
    container.Generate_particle(25, 15, 0, -6, 10.0f, "red");
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y > 0); // particle is now moving in other direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 15); // particle is back to starting position after next frame
  }

  SECTION("Up and rightward collision with right wall") {
    container.Generate_particle(35, 20, 6, 5, 10.0f, "red"); // particle at (35,20) with velocity vect(6,5)
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().x < 0); // particle is now moving in opposite x direction, same y direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 30);
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 35);
  }

  SECTION("down and rightward collision with right wall") {
    container.Generate_particle(35, 30, 6, -5, 10.0f, "red");
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().x < 0);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 20); // particle is back to starting position after next frame
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 35); // particle is back to starting position after next frame
  }

  SECTION("Up and leftward collision with left wall") {
    container.Generate_particle(15, 20, -6, 5, 10.0f, "red"); // particle at (35,20) with velocity vect(6,5)
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().x > 0); // particle is now moving in opposite x direction, same y direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 30);
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 15);
  }

  SECTION("down and leftward collision with left wall") {
    container.Generate_particle(15, 30, -6, -5, 10.0f, "red");
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().x > 0);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 20); // particle is back to starting position after next frame
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 15); // particle is back to starting position after next frame
  }

  SECTION("Up and rightward collision with top wall") {
    container.Generate_particle(20, 15, 5, -6, 10.0f, "red");
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y > 0); // particle is now moving in opposite y direction, same y direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 15);
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 30);
  }

  SECTION("Up and leftward collision with top wall") {
    container.Generate_particle(30, 15, -5, -6, 10.0f, "red");
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y > 0);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 15); // particle is back to starting position after next frame
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 20); // particle is back to starting position after next frame
  }

  SECTION("Down and leftward collision with bottom wall") {
    container.Generate_particle(30, 35, -5, 6, 10.0f, "red");
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y < 0); // particle is now moving in opposite y direction, same y direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 35);
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 20);
  }

  SECTION("Down and rightward collision with bottom wall") {
    container.Generate_particle(20, 35, 5, 6, 10.0f, "red");
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 25); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y < 0);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 35); // particle is back to starting position after next frame
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 30); // particle is back to starting position after next frame
  }

  SECTION("Top right corner wall collision") {
    container.Generate_particle(35, 15, 6, -6, 10.0f, "red");
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y > 0); // particle is now moving in opposite y direction
    REQUIRE(container.Get_particles().at(0).GetVelocity().x < 0); // particle is now moving in opposite x direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 15);
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 35);
  }

  SECTION("Bottom right corner wall collision") {
    container.Generate_particle(35, 35, 6, 6, 10.0f, "red");
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y < 0);
    REQUIRE(container.Get_particles().at(0).GetVelocity().x < 0);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 35); // particle is back to starting position after next frame
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 35); // particle is back to starting position after next frame
  }

  SECTION("Top left corner wall collision") {
    container.Generate_particle(15, 15, -6, -6, 10.0f, "red");
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y > 0); // particle is now moving in opposite y direction
    REQUIRE(container.Get_particles().at(0).GetVelocity().x > 0); // particle is now moving in opposite x direction
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 15);
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 15);
  }

  SECTION("Bottom left corner wall collision") {
    container.Generate_particle(15, 35, -6, 6, 10.0f, "red");
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 9); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 41); // particle is technically past wall boundary with r = 10
    REQUIRE(container.Get_particles().at(0).GetVelocity().y < 0);
    REQUIRE(container.Get_particles().at(0).GetVelocity().x > 0);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 35); // particle is back to starting position after next frame
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 15); // particle is back to starting position after next frame
  }

}

TEST_CASE("Inter-particle collisions", "[particle][collision]") {

  Gas_container container(glm::vec2(0,0), 50);

  SECTION("Perfectly horizontal collision with two particles") {
    container.Generate_particle(13, 25, 3, 0, 10.0f, "red");
    container.Generate_particle(37, 25, -3, 0, 10.0f, "red");
    container.Update(); // particles should now be touching
    REQUIRE(glm::distance(container.Get_particles().at(0).GetPosition(),
                          container.Get_particles().at(1).GetPosition()) <= 20);
    REQUIRE(container.Get_particles().at(0).GetVelocity().x == -3); // swap directions in velocity
    REQUIRE(container.Get_particles().at(1).GetVelocity().x == 3);
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 25);
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 13);
    REQUIRE(container.Get_particles().at(1).GetPosition().y == 25);
    REQUIRE(container.Get_particles().at(1).GetPosition().x == 37);
  }

  SECTION("Perfectly vertical collision with two particles") {
    container.Generate_particle(25, 13, 0, 3, 10.0f, "red");
    container.Generate_particle(25, 37, 0, -3, 10.0f, "red");
    container.Update(); // particles should now be touching
    REQUIRE(glm::distance(container.Get_particles().at(0).GetPosition(),
                          container.Get_particles().at(1).GetPosition()) <= 20);
    REQUIRE(container.Get_particles().at(0).GetVelocity().y == -3); // swap directions in velocity
    REQUIRE(container.Get_particles().at(1).GetVelocity().y == 3);
    container.Update(); // particles should now be touching
    REQUIRE(container.Get_particles().at(0).GetPosition().y == 13);
    REQUIRE(container.Get_particles().at(0).GetPosition().x == 25);
    REQUIRE(container.Get_particles().at(1).GetPosition().y == 37);
    REQUIRE(container.Get_particles().at(1).GetPosition().x == 25);
  }

  SECTION("Particle 1 moving in the +x, +y direction collides with particle 2 moving in the +x, +y direction") {
    container.Generate_particle(25, 15, 3, 3, 10.0f, "red");
    container.Generate_particle(25, 36, 3, 1, 10.0f, "red");
    container.Update(); // particles should now be touching
    REQUIRE(glm::distance(container.Get_particles().at(0).GetPosition(),
                          container.Get_particles().at(1).GetPosition()) <= 20);
    REQUIRE(container.Get_particles().at(0).GetVelocity() == glm::vec2(3,1));
    REQUIRE(container.Get_particles().at(1).GetVelocity() == glm::vec2(3,3));
    container.Update();
    REQUIRE(container.Get_particles().at(0).GetPosition() == glm::vec2(31,19));
    REQUIRE(container.Get_particles().at(1).GetPosition() == glm::vec2(31,40));
  }

  SECTION("Particle 1 moving in the +x, +y direction collides with particle 2 moving in the +x, -y direction") {
    container.Generate_particle(25, 15, 3, 3, 10.0f, "red");
    container.Generate_particle(25, 36, 3, -3, 10.0f, "red");
    container.Update(); // particles should now be touching
    REQUIRE(glm::distance(container.Get_particles().at(0).GetPosition(),
                          container.Get_particles().at(1).GetPosition()) <= 20);
    REQUIRE(container.Get_particles().at(0).GetVelocity() == glm::vec2(3,-3));
    REQUIRE(container.Get_particles().at(1).GetVelocity() == glm::vec2(3,3));
  }

  SECTION("Particle 1 moving in the +x, +y direction collides with particle 2 moving in the -x, +y direction") {
    container.Generate_particle(14, 15, 3, 3, 10.0f, "red");
    container.Generate_particle(36, 15, -3, 3, 10.0f, "red");
    container.Update(); // particles should now be touching
    REQUIRE(glm::distance(container.Get_particles().at(0).GetPosition(),
                          container.Get_particles().at(1).GetPosition()) <= 20);
    REQUIRE(container.Get_particles().at(0).GetVelocity() == glm::vec2(-3,3));
    REQUIRE(container.Get_particles().at(1).GetVelocity() == glm::vec2(3,3));
  }

  SECTION("Particle 1 moving in the +x, +y direction collides with particle 2 moving in the -x, -y direction") {
    container.Generate_particle(16, 16, 3, 3, 10.0f, "red");
    container.Generate_particle(35, 35, -3, -3, 10.0f, "red");
    container.Update(); // particles should now be touching
    REQUIRE(glm::distance(container.Get_particles().at(0).GetPosition(),
                          container.Get_particles().at(1).GetPosition()) <= 20);
    REQUIRE(container.Get_particles().at(0).GetVelocity().x == Approx(-3));
    REQUIRE(container.Get_particles().at(0).GetVelocity().y == Approx(-3));
    REQUIRE(container.Get_particles().at(1).GetVelocity().x == Approx(3));
    REQUIRE(container.Get_particles().at(1).GetVelocity().y == Approx(3));
  }

  SECTION("Particle 1 moving in the +x, -y direction collides with particle 2 moving in the +x, -y direction") {
    container.Generate_particle(25, 14, 3, -3, 10.0f, "red");
    container.Generate_particle(25, 35, 5, -5, 10.0f, "red");
    container.Update(); // particles should now be touching
    REQUIRE(glm::distance(container.Get_particles().at(0).GetPosition(),
                          container.Get_particles().at(1).GetPosition()) <= 20);
    REQUIRE(container.Get_particles().at(0).GetVelocity().x == Approx(2.8137));
    REQUIRE(container.Get_particles().at(0).GetVelocity().y == Approx(-4.76986));
    REQUIRE(container.Get_particles().at(1).GetVelocity().x == Approx(5.1863));
    REQUIRE(container.Get_particles().at(1).GetVelocity().y == Approx(-3.23014));
  }

  SECTION("Particle 1 moving in the +x, -y direction collides with particle 2 moving in the -x, +y direction") {
    container.Generate_particle(35, 16, -5, 5, 10.0f, "red");
    container.Generate_particle(16, 35, 5, -5, 10.0f, "red");
    container.Update(); // particles should now be touching
    REQUIRE(glm::distance(container.Get_particles().at(0).GetPosition(),
                          container.Get_particles().at(1).GetPosition()) <= 20);
    REQUIRE(container.Get_particles().at(0).GetVelocity().x == Approx(5));
    REQUIRE(container.Get_particles().at(0).GetVelocity().y == Approx(-5));
    REQUIRE(container.Get_particles().at(1).GetVelocity().x == Approx(-5));
    REQUIRE(container.Get_particles().at(1).GetVelocity().y == Approx(5));
  }

  SECTION("Particle 1 moving in the +x, -y direction collides with particle 2 moving in the -x, -y direction") {
    container.Generate_particle(35, 16, -5, -5, 10.0f, "red");
    container.Generate_particle(16, 16, 5, -5, 10.0f, "red");
    container.Update(); // particles should now be touching
    REQUIRE(glm::distance(container.Get_particles().at(0).GetPosition(),
                          container.Get_particles().at(1).GetPosition()) <= 20);
    REQUIRE(container.Get_particles().at(0).GetVelocity().x == Approx(5));
    REQUIRE(container.Get_particles().at(0).GetVelocity().y == Approx(-5));
    REQUIRE(container.Get_particles().at(1).GetVelocity().x == Approx(-5));
    REQUIRE(container.Get_particles().at(1).GetVelocity().y == Approx(-5));
  }

  SECTION("Particle 1 moving in the -x, +y direction collides with particle 2 moving in the -x, +y direction") {
    container.Generate_particle(35, 25, -5, 4, 10.0f, "red");
    container.Generate_particle(14, 25, -3, 5, 10.0f, "red");
    container.Update(); // particles should now be touching
    REQUIRE(glm::distance(container.Get_particles().at(0).GetPosition(),
                          container.Get_particles().at(1).GetPosition()) <= 20);
    REQUIRE(container.Get_particles().at(0).GetVelocity().x == Approx(-3.05801));
    REQUIRE(container.Get_particles().at(0).GetVelocity().y == Approx(3.89779));
    REQUIRE(container.Get_particles().at(1).GetVelocity().x == Approx(-4.94199));
    REQUIRE(container.Get_particles().at(1).GetVelocity().y == Approx(5.10221));
  }

  SECTION("Particle 1 moving in the -x, +y direction collides with particle 2 moving in the -x, -y direction") {
    container.Generate_particle(35, 35, -3, -3, 10.0f, "red");
    container.Generate_particle(35, 14, -3, 3, 10.0f, "red");
    container.Update(); // particles should now be touching
    REQUIRE(glm::distance(container.Get_particles().at(0).GetPosition(),
                          container.Get_particles().at(1).GetPosition()) <= 20);
    REQUIRE(container.Get_particles().at(0).GetVelocity().x == Approx(-3));
    REQUIRE(container.Get_particles().at(0).GetVelocity().y == Approx(3));
    REQUIRE(container.Get_particles().at(1).GetVelocity().x == Approx(-3));
    REQUIRE(container.Get_particles().at(1).GetVelocity().y == Approx(-3));
  }

  SECTION("Particle 1 moving in the -x, -y direction collides with particle 2 moving in the -x, -y direction") {
    container.Generate_particle(35, 35, -3, -5, 10.0f, "red");
    container.Generate_particle(35, 14, -4, -2, 10.0f, "red");
    container.Update(); // particles should now be touching
    REQUIRE(glm::distance(container.Get_particles().at(0).GetPosition(),
                          container.Get_particles().at(1).GetPosition()) <= 20);
    REQUIRE(container.Get_particles().at(0).GetVelocity().x == Approx(-2.8369));
    REQUIRE(container.Get_particles().at(0).GetVelocity().y == Approx(-2.0646));
    REQUIRE(container.Get_particles().at(1).GetVelocity().x == Approx(-4.16308));
    REQUIRE(container.Get_particles().at(1).GetVelocity().y == Approx(-4.93538));
  }

  SECTION("Particle 1 moving in the +x, 0 direction collides with stationary particle 2") {
    container.Generate_particle(15, 25, 3, 0, 10.0f, "red");
    container.Generate_particle(36, 25, 0, 0, 10.0f, "red");
    container.Update(); // particles should now be touching
    REQUIRE(glm::distance(container.Get_particles().at(0).GetPosition(),
                          container.Get_particles().at(1).GetPosition()) <= 20);
    REQUIRE(container.Get_particles().at(0).GetVelocity().x == Approx(0));
    REQUIRE(container.Get_particles().at(0).GetVelocity().y == Approx(0));
    REQUIRE(container.Get_particles().at(1).GetVelocity().x == Approx(3));
    REQUIRE(container.Get_particles().at(1).GetVelocity().y == Approx(0));
  }
}

TEST_CASE("Histogram generation", "[histogram]") {
  Gas_container container(glm::vec2(0, 0), 50);
  GasHistogram hist(glm::vec2(0, 0));
  container.Generate_particle(15, 25, 3, 0, 10.0f, "red");
  hist.Update(container.Get_particles());
  hist.Display();

}

} // namespace container

} // namespace idealgas

