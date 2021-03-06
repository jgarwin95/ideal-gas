#include <gas_container.h>
#include <math.h>

namespace idealgas {

namespace container {

using glm::vec2;

Gas_container::Gas_container(const glm::vec2 &top_left_corner, double container_size) :
  top_left_corner_(top_left_corner), container_size_(container_size){
  vec2 bottom_right =
      top_left_corner_ + vec2(container_size_, container_size_);

  container_rect_ = ci::Rectf(top_left_corner_, bottom_right);
  // place single particle in the middle of the container
}

Gas_container::~Gas_container() {
  for (Gas_Particle *particle : particles_) {
    delete particle;
    particle = nullptr;
  }
}

void Gas_container::Generate_particle(std::string& color) {
  if (color == "red") {
    Gas_Particle *red_temp  = new Gas_Particle(top_left_corner_ + glm::vec2(container_size_/2, container_size_/2),
                      glm::vec2(4, -2), 10.0f, "red");
    particles_.push_back(red_temp);
    red_particles.push_back(red_temp);

  } else if (color == "blue") {
    Gas_Particle *blue_temp  = new Gas_Particle(top_left_corner_ + glm::vec2(container_size_/2, container_size_/2),
                                               glm::vec2(3, -2), 18.0f, "blue");
    particles_.push_back(blue_temp);
    blue_particles.push_back(blue_temp);
  }

  else if (color == "green") {
    Gas_Particle *green_temp  = new Gas_Particle(top_left_corner_ + glm::vec2(container_size_/2, container_size_/2),
                                                glm::vec2(2, -1.8), 27.0f, "green");
    particles_.push_back(green_temp);
    green_particles.push_back(green_temp);
  }
}

void Gas_container::Generate_particle(int x_loc, int y_loc, int x_vel, int y_vel, float radius, const char* color) {
  Gas_Particle *temp  = new Gas_Particle(glm::vec2(x_loc, y_loc), glm::vec2(x_vel, y_vel), radius, color);
  particles_.push_back(temp);
}

void Gas_container::Draw() const {

  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(container_rect_);

  // draw each particle
  for (Gas_Particle* particle : particles_) {
    particle->draw();
  }
}

void Gas_container::Update()  {
  // Reset max speed
  max_speed_ = 0;

  for (Gas_Particle* particle : particles_) {
    // Move each particle to it's final position for this frame
    particle->Move();
  }

  int particle_counter = 0;
  // Handle any collisions associated with those final positions
  for (Gas_Particle* particle : particles_) {

    //float radius = particle.GetRadius();
    float radius = particle->GetRadius();

    // check if the particle is touching a left/right wall
    if (((particle->GetPosition().x  - radius <= container_rect_.x1) && CheckOppositeDirection(particle, "left")) ||
        ((particle->GetPosition().x  + radius >= container_rect_.x2) && CheckOppositeDirection(particle, "right"))) {
      // Flip x direction
      particle->ReverseXDirection();
    }
    // check if the particle is touching a top/bottom wall
    if (((particle->GetPosition().y  + radius >= container_rect_.y2) && CheckOppositeDirection(particle, "bottom")) ||
        ((particle->GetPosition().y  - radius <= container_rect_.y1) && CheckOppositeDirection(particle, "top"))) {
      // Flip y direction
      particle->ReverseYDirection();
    }

    for (size_t i = particle_counter + 1; i < particles_.size(); i++) {
      Gas_Particle* other = particles_.at(i);
      // If they are touching and were heading in the same direction handle collision
      if (Check_collision(particle, other) && CheckOppositeDirection(particle, other)) {
        HandleCollision(particle, other);
      }
    }
    // Increment current particle number
    particle_counter++;

    if (glm::length(particle->GetVelocity()) > max_speed_) {
      max_speed_ = glm::length(particle->GetVelocity());
    }
  }
}

void Gas_container::HandleCollision(Gas_Particle* particle_1, Gas_Particle* particle_2) {
  // Save initial state of particles
  glm::vec2 vi_1 = particle_1->GetVelocity();
  glm::vec2 vi_2 = particle_2->GetVelocity();
  glm::vec2 xi_1 = particle_1->GetPosition();
  glm::vec2 xi_2 = particle_2->GetPosition();
  float m1 = particle_1->GetMass();
  float m2 = particle_2->GetMass();
  // Alter velocities based on previously saved state
  particle_1->Handle_collision(vi_2, xi_2, m2);
  particle_2->Handle_collision(vi_1, xi_1, m1);
}

bool Gas_container::Check_collision(const Gas_Particle* particle_1, const Gas_Particle* particle_2) {
  glm::vec2 pos1 = particle_1->GetPosition();
  glm::vec2 pos2 = particle_2->GetPosition();
  // return if the sum of the radii is less than the distance between the centers of the two particles
  return (particle_1->GetRadius() + particle_2->GetRadius() >= glm::distance(particle_1->GetPosition(), particle_2->GetPosition()));
}

bool Gas_container::CheckOppositeDirection(const Gas_Particle* particle_1, const Gas_Particle* particle_2) const {
  float result = glm::dot(particle_1->GetVelocity() - particle_2->GetVelocity(), particle_1->GetPosition() - particle_2->GetPosition());
  return (result < 0);
}

bool Gas_container::CheckOppositeDirection(const Gas_Particle* particle, std::string&& direction) const {
  glm::vec2 wall_position;
  if (direction == "left")
    wall_position = glm::vec2(container_rect_.getX1(), particle->GetPosition().y);
  else if (direction == "right")
    wall_position = glm::vec2(container_rect_.getX2(), particle->GetPosition().y);
  else if (direction == "top")
    wall_position = glm::vec2(particle->GetPosition().x, container_rect_.getY1());
  else if (direction == "bottom")
    wall_position = glm::vec2(particle->GetPosition().x, container_rect_.getY2());

  float result = glm::dot(particle->GetVelocity(), particle->GetPosition() - wall_position);

  // If particle is outside the confines of the box the rules for direction switching are reverse
  // Only switch if the particle is heading away from the boundary, if it is heading towards to not switch
  if (IsOutsideBox(particle) && (result > 0)) {
    return true;
  } else if (IsOutsideBox(particle) && (result < 0)) {
    return false;
  } else {
    return result < 0;
  }
}

const std::vector<Gas_Particle*>& Gas_container::Get_particles() const {
  return particles_;
}

const std::vector<Gas_Particle *> &Gas_container::GetRedParticles() const {
  return red_particles;
}

const std::vector<Gas_Particle *> &Gas_container::GetBlueParticles() const {
  return blue_particles;
}

const std::vector<Gas_Particle *> &Gas_container::GetGreenParticles() const {
  return green_particles;
}

void Gas_container::Clear() {
  particles_.clear();
}

void Gas_container::IncreaseParticleSpeed() {
  for (Gas_Particle* particle : particles_) {
    particle->IncreaseSpeed();
  }
}

void Gas_container::DecreaseParticleSpeed() {
  for (Gas_Particle* particle : particles_) {
    particle->DecreaseSpeed();
  }
}
const cinder::Rectf &Gas_container::GetContainerRect() const {
  return container_rect_;
}

double Gas_container::GetMaxSpeed() {
  return max_speed_;
}

bool Gas_container::IsOutsideBox(const Gas_Particle *p_particle) const {
  if ((p_particle->GetPosition().x > container_rect_.x2) || (p_particle->GetPosition().x < container_rect_.x1)) {
    return true;
  }
  if ((p_particle->GetPosition().y > container_rect_.y2) || (p_particle->GetPosition().y < container_rect_.y1)) {
    return true;
  }
  return false;
}

}  // namespace container

}  // namespace idealgas
