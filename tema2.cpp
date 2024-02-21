
#include "lab_m1/tema2/tema2.h"
#include <vector>
#include <random>
#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include "utils/glm_utils.h"
#include "utils/math_utils.h"
//#include "lab_m1/lab5/lab_camera.h"
using namespace std;
using namespace m1;
vector<Building> blocks;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

Player player = Player(0.0f, 0.12f, 0.0f, 0.0f, 0.0f);

vector<Tank> opponents;

Tema2::Tema2() {

}


Tema2::~Tema2() {
}


void Tema2::Init() {
    score = 0;
    {
        loser = false;
        winner = false;
        // Light & material properties
        {
            lightPosition = glm::vec3(0, 1, 1);
            materialShininess = 100;
            materialKd = 0.5;
            materialKs = 0.5;

        }

        for (int i = 0; i < 5; i++) {
            std::random_device rd;
            std::mt19937 gen(rd());
            // Define the range for X, Y, and Z coordinates
            std::uniform_real_distribution<float> xDist(-10.0f, -2.0f);
            std::uniform_real_distribution<float> zDist(-2.0f, 10.0f);
            float randomX = xDist(gen);
            float randomZ = zDist(gen);
            Tank enemy = Tank(randomX, 0.12f, randomZ, 0.0f, 0.0f, MovementState::GoingForward,
                              MovementState::GoingForward, 0.0f, 0.0f);
            opponents.push_back(enemy);
        }
        sum = 0.0f;
        gameTime = 0.0f;
        ttl = 2.0f;
        timeSinceLastProj = 0.0f;
        k = 0;
        tx = player.getTx();
        tz = player.getTz();
        renderCameraTarget = false;
        fov = 60.0f;
        height = 30.0f;
        width = 30.0f;

        camera1 = new implemented::Camera1();
        camera1->position = glm::vec3(player.getTx() + 1.5f, player.getTy() + 0.58f, player.getTz());
        camera1->Set(camera1->position, glm::vec3(player.getTx(), player.getTy(), player.getTz()), glm::vec3(0, 1, 0));
        {
            Mesh *mesh = new Mesh("bloc1");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "world"), "bloc1.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }
        {
            Mesh *mesh = new Mesh("bloc6");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "world"), "bloc6.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }
        {
            Mesh *mesh = new Mesh("bloc7");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "world"), "bloc7.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }

        {
            Mesh *mesh = new Mesh("bloc2");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "world"), "bloc2.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }
        {
            Mesh *mesh = new Mesh("bloc3");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "world"), "bloc3.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }
        {
            Mesh *mesh = new Mesh("bloc4");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "world"), "bloc4.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }
        {
            Mesh *mesh = new Mesh("bloc5");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "world"), "bloc5.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }
        {
            Mesh *mesh = new Mesh("munitie");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "player_tank"), "munitie.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }
        {
            Mesh *mesh = new Mesh("main_body");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "player_tank"), "main_body.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }
        {
            Mesh *mesh = new Mesh("main_senile");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "player_tank"), "main_senile.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }
        {
            Mesh *mesh = new Mesh("main_turela");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "player_tank"), "main_turela.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }
        {
            Mesh *mesh = new Mesh("main_tun");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "player_tank"), "main_tun.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }
        {
            Mesh *mesh = new Mesh("plane50");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }
        Shader *shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"),
                          GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"),
                          GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    // TODO(student): After you implement the changing of the projection
    // parameters, remove hardcodings of these parameters
    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 200.0f);
    Building b1 = Building(0.5f, -5.0f, 0.0f, 2.572);
    Building b4 = Building(0.5f, -10.0f, 0.0f, -4);
    Building b3 = Building(0.3f, -7.0f, 0.0f, 1);
    Building b2 = Building(0.2f, -4.0f, 0.0f, -2.572);;
    Building b5 = Building(0.5f, -8.0f, 0.0f, -9);
    Building b6 = Building(0.5f, -8.0f, 0.0f, 9);

    blocks.push_back(b1);
    blocks.push_back(b4);

    blocks.push_back(b3);
    blocks.push_back(b2);
    blocks.push_back(b5);
    blocks.push_back(b6);

}


void Tema2::FrameStart() {
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor((float) 128 / 255, (float) 218 / 255, (float) 235 / 255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x / 2, resolution.y / 2);
}

int GetRandomNumberInRange(const int minInclusive, const int maxInclusive) {
    static std::random_device randomDevice;
    static std::default_random_engine randomEngine(randomDevice());

    std::uniform_int_distribution<int> uniformDist(minInclusive, maxInclusive);

    return uniformDist(randomEngine);
}

MovementState GetNextMovementState(const MovementState currentState) {
    int randomChange = GetRandomNumberInRange(0, 1);
    MovementState nextState = currentState;

    switch (currentState) {
        case MovementState::GoingForward:
        case MovementState::GoingBackward:
            nextState = (randomChange == 1)
                        ? MovementState::InPlaceRotationLeft
                        : MovementState::InPlaceRotationRight;
            break;

        case MovementState::InPlaceRotationLeft:
        case MovementState::InPlaceRotationRight:
            nextState = (randomChange == 1)
                        ? MovementState::GoingForward
                        : MovementState::GoingBackward;
            break;

        default:
            break;
    }

    return nextState;
}

std::string GetMovementStateName(const MovementState state) {
    static const std::map<MovementState, std::string> kStateNames
            {
                    {MovementState::GoingForward,         "GoingForward"},
                    {MovementState::GoingBackward,        "GoingBackward"},
                    {MovementState::InPlaceRotationLeft,  "InPlaceRotationLeft"},
                    {MovementState::InPlaceRotationRight, "InPlaceRotationRight"},
            };

    std::string s = "";

    if (kStateNames.find(state) != kStateNames.end()) {
        s = kStateNames.at(state);
    }

    return s;
}


void Tema2::RenderSimple(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color, float hp) {
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Use the shader program
    glUseProgram(shader->program);

    // Set shader uniforms for light & material properties
    glUniform3fv(glGetUniformLocation(shader->program, "light_position"), 1, glm::value_ptr(lightPosition));
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    glUniform3fv(glGetUniformLocation(shader->program, "eye_position"), 1, glm::value_ptr(eyePosition));
    glUniform1f(glGetUniformLocation(shader->program, "material_kd"), materialKd);
    glUniform1f(glGetUniformLocation(shader->program, "material_ks"), materialKs);
    glUniform1i(glGetUniformLocation(shader->program, "material_shininess"), materialShininess);
    glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));
    glUniform1f(glGetUniformLocation(shader->program, "hp"), hp);

    // Set matrix uniforms
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera1->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);

    // Stop using the shader program (optional if needed elsewhere)
    shader->Use();
    mesh->Render();
}

void Tema2::CollisionPlayerBlocks() {
    for (auto &bloc: blocks) {
        glm::vec3 enemyCenter(bloc.getBx(), bloc.getBy(), bloc.getBz());
        glm::vec3 opCenter(player.getTx(), player.getTy(), player.getTz());
        float distance = glm::distance(enemyCenter, opCenter);
        float tankRadius = 0.75f;
        float blockRadius = bloc.getWidth();
        if (distance < tankRadius + blockRadius) {
            //collision detected
            //|P| = ( Raza_Tanc_1 + Raza_Tanc_2 - Distanta_Intre_Tancuri )
            float p = tankRadius + blockRadius - distance;
            //Dif = ( Centru_Tanc_2 - Centru_Tanc_1 )
            glm::vec3 diff(enemyCenter - opCenter);
            //P = |P| * glm::Normalize( Dif )
            glm::vec3 poz = p * glm::normalize(diff);
            //Centru_Tanc_1  += P * -0.5f;
            //Centru_Tanc_2  += P * 0.5f;
            //enemyCenter+=p*0.5f;
            opCenter += poz * (-0.5f);
            //opponent.setEy(opCenter.y);
            player.setTz(opCenter.z);
            player.setTx(opCenter.x);
        }
    }
}

void Tema2::CollisionEnemiesBlocks() {
    for (auto &bloc: blocks) {
        for (auto &enemy: opponents) {
            glm::vec3 enemyCenter(bloc.getBx(), bloc.getBy(), bloc.getBz());
            glm::vec3 opCenter(enemy.getX(), enemy.getY(), enemy.getZ());
            float distance = glm::distance(enemyCenter, opCenter);

            float tankRadius = 0.75f;
            float blockRadius = bloc.getWidth();
            if (distance < tankRadius + blockRadius) {
                //collision detected
                //|P| = ( Raza_Tanc_1 + Raza_Tanc_2 - Distanta_Intre_Tancuri )
                float p = tankRadius + blockRadius - distance;
                //Dif = ( Centru_Tanc_2 - Centru_Tanc_1 )
                glm::vec3 diff(enemyCenter - opCenter);
                //P = |P| * glm::Normalize( Dif )
                glm::vec3 poz = p * glm::normalize(diff);
                //Centru_Tanc_1  += P * -0.5f;
                //Centru_Tanc_2  += P * 0.5f;
                //enemyCenter+=p*0.5f;
                opCenter += poz * (-0.5f);
                //opponent.setEy(opCenter.y);
                enemy.setZ(opCenter.z);
                enemy.setX(opCenter.x);
            }
        }
    }
}

void Tema2::CollisionProjEnemy() {
    for (auto &enemy: opponents) {
        for (auto &proj: player.munitie) {
            if (!proj.isRender()) {
                proj.setRender(false);
            }
            glm::vec3 tankCenter(enemy.getX(), enemy.getY(), enemy.getZ());
            glm::vec3 projectileCenter(proj.getPx(), proj.getPy(), proj.getPz());
            float distance = glm::distance(tankCenter, projectileCenter);
            float tankRadius = 0.9236f;
            float projectileRadius = 0.024f;

            if (distance < tankRadius + projectileRadius) {
                proj.setRender(false);
                if (!proj.isHit()) {
                    enemy.setHp(enemy.getHp() - 1);
                    proj.setHit(true);
                }
            }

        }
    }
}

void Tema2::CollisionProjPlayer() {
    for (auto &enemy: opponents) {
        for (auto &proj: enemy.munitie) {
            if (!proj.isRender()) {
                proj.setRender(false);
            }
            glm::vec3 tankCenter(player.getTx(), player.getTy(), player.getTz());
            glm::vec3 projectileCenter(proj.getPx(), proj.getPy(), proj.getPz());
            float distance = glm::distance(tankCenter, projectileCenter);
            float tankRadius = 0.9236f;
            float projectileRadius = 0.024f;
            //  cout<<"hp:"<<player.getHp()<<endl;
            if (distance < tankRadius + projectileRadius) {
                proj.setRender(false);
                if (!proj.isHit()) {
                    player.setHp(player.getHp() - 1);
                    proj.setHit(true);
                }

            }

        }
    }
}

void Tema2::CollisionProjBlock(vector<Proiectil> v) {
    for (auto &block: blocks) {
        for (auto &proj: v) {
            if (!proj.isRender()) {
                proj.setRender(false);
            }
            glm::vec3 blockCenter(block.getBx(), block.getBy(), block.getBz());
            glm::vec3 projectileCenter(proj.getPx(), proj.getPy(), proj.getPz());
            float distance = glm::distance(blockCenter, projectileCenter);
            float blockRadius = block.getWidth();
            float projectileRadius = 1.0f;

            if (distance < blockRadius + projectileRadius) {
                proj.setRender(false);
            }

        }
    }
}

void Tema2::CollisionTankTank() {
    for (auto &enemy: opponents) {
        for (auto &opponent: opponents) {
            if (enemy.getX() == opponent.getX() && enemy.getZ() == opponent.getZ()) {
                continue;
            }
            glm::vec3 enemyCenter(enemy.getX(), enemy.getY(), enemy.getZ());
            glm::vec3 opCenter(opponent.getX(), opponent.getY(), opponent.getZ());
            float distance = glm::distance(enemyCenter, opCenter);
            float tankRadius = 0.75f;
            if (distance < 2 * tankRadius) {
                //collision detected
                //|P| = ( Raza_Tanc_1 + Raza_Tanc_2 - Distanta_Intre_Tancuri )
                float p = tankRadius * 2 - distance;
                //Dif = ( Centru_Tanc_2 - Centru_Tanc_1 )
                glm::vec3 diff(enemyCenter - opCenter);
                //P = |P| * glm::Normalize( Dif )
                glm::vec3 poz = p * glm::normalize(diff);
                //Centru_Tanc_1  += P * -0.5f;
                //Centru_Tanc_2  += P * 0.5f;
                enemyCenter += poz * 0.5f;
                opCenter += poz * (-0.5f);
                enemy.setX(enemyCenter.x);
                // enemy.setEy(enemyCenter.y);
                enemy.setZ(enemyCenter.z);
                opponent.setX(opCenter.x);
                //opponent.setEy(opCenter.y);
                opponent.setZ(opCenter.z);
            }
        }
    }
}

void Tema2::CollisionPlayerEnemy() {
    for (auto &enemy: opponents) {
        glm::vec3 enemyCenter(enemy.getX(), enemy.getY(), enemy.getZ());
        glm::vec3 opCenter(player.getTx(), player.getTy(), player.getTz());
        float distance = glm::distance(enemyCenter, opCenter);
        float tankRadius = 0.8f;
        if (distance < 2 * tankRadius) {
            //collision detected
            //|P| = ( Raza_Tanc_1 + Raza_Tanc_2 - Distanta_Intre_Tancuri )
            float p = tankRadius * 2 - distance;
            //Dif = ( Centru_Tanc_2 - Centru_Tanc_1 )
            glm::vec3 diff = glm::vec3(opCenter - enemyCenter);
            //P = |P| * glm::Normalize( Dif )
            glm::vec3 poz = p * glm::normalize(diff);
            //Centru_Tanc_1  += P * -0.5f;
            //Centru_Tanc_2  += P * 0.5f;
            enemyCenter += poz * (-0.5f);
            opCenter += poz * (0.5f);
            enemy.setX(enemyCenter.x);
            // enemy.setEy(enemyCenter.y);
            enemy.setZ(enemyCenter.z);
            player.setTx(opCenter.x);
            //opponent.setEy(opCenter.y);
            player.setTz(opCenter.z);
        }
    }
}

void Tema2::EnemyAttack() {
    for (auto &enemy: opponents) {
        Proiectil proj = Proiectil(enemy.getX(), enemy.getY(), enemy.getZ(), enemy.getAngle(), 2.0f, true);
        glm::vec3 enemyCenter(enemy.getX(), enemy.getY(), enemy.getZ());
        glm::vec3 opCenter(player.getTx(), player.getTy(), player.getTz());
        float distance = glm::distance(enemyCenter, opCenter);

        if (distance < 4.0f) {
            glm::vec3 direction = glm::normalize(opCenter - enemyCenter);
            float yaw = atan2(direction.x, direction.z);
            float angleInDegrees = glm::degrees(yaw);
            enemy.setAngle(angleInDegrees + 90.0f);
            if (enemy.getTimeSinceLastProj() >= 1.0f) {
                enemy.munitie.push_back(proj);
                enemy.setTimeSinceLastProj(0.0f);
            }

        } else {
            enemy.setAngle(enemy.getRotate());
            proj.setRender(false);
        }
    }
}

void Tema2::RenderEnemy(float deltatime) {
    for (auto &enemy: opponents) {
        string name;
        sum += deltatime;
        name = GetMovementStateName(enemy.getState());
        if (sum > 5.0f) {
            sum = 0.0f;
            enemy.setNextState(GetNextMovementState(enemy.getState()));
            enemy.setState(enemy.getNextState());
            name = GetMovementStateName(enemy.getState());
        }
        if (enemy.getHp() > 1 and gameTime<60.0f) {
            if (name == "InPlaceRotationRight") {
                enemy.rotateRight(deltatime);


            } else if (name == "GoingForward") {
                enemy.moveForward(deltatime);

            } else if (name == "InPlaceRotationLeft") {
                enemy.rotateLeft(deltatime);

            } else if (name == "GoingBackward") {
                enemy.moveBackward(deltatime);

            }
        }

        EnemyAttack();
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(enemy.getX(), enemy.getY(), enemy.getZ()));
            modelMatrix = glm::rotate(modelMatrix, RADIANS(enemy.getRotate()), glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
            RenderSimple(meshes["main_body"], shaders["LabShader"], modelMatrix,
                         glm::vec3((float) 21 / 255, (float) 128 / 255, (float) 120 / 255), enemy.getHp());
        }
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(enemy.getX(), enemy.getY(), enemy.getZ()));
            modelMatrix = glm::rotate(modelMatrix, RADIANS(enemy.getRotate()), glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
            RenderSimple(meshes["main_senile"], shaders["LabShader"], modelMatrix,
                         glm::vec3((float) 247 / 255, (float) 128 / 255, (float) 181 / 255), enemy.getHp());
        }
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(enemy.getX(), enemy.getY(), enemy.getZ()));
            modelMatrix = glm::rotate(modelMatrix, RADIANS(enemy.getAngle()), glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
            RenderSimple(meshes["main_turela"], shaders["LabShader"], modelMatrix,
                         glm::vec3((float) 197 / 255, (float) 227 / 255, (float) 132 / 255), enemy.getHp());
        }
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(enemy.getX(), enemy.getY(), enemy.getZ()));
            modelMatrix = glm::rotate(modelMatrix, RADIANS(enemy.getAngle()), glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
            RenderSimple(meshes["main_tun"], shaders["LabShader"], modelMatrix,
                         glm::vec3((float) 247 / 255, (float) 128 / 255, (float) 181 / 255), enemy.getHp());
        }
    }
}

void Tema2::Update(float deltaTimeSeconds) {
//    if(gameTime>=60.0f){
//        return;
//    }
    if (gameTime >= 60.0f && !loser && !winner) {
        cout << "Great job, soldier, you shot " << score << " enemies" << endl;
        cout << "Tank you for your service<3" << endl;
        winner = true;
    }
    for (auto &enemy: opponents) {
        if (!enemy.isAddedToScore() && enemy.getHp() <= 1) {
            score += 1;
            enemy.setAddedToScore(true);
        }
    }
    gameTime += deltaTimeSeconds;
    timeSinceLastProj += deltaTimeSeconds;
    ttl -= deltaTimeSeconds;
    CollisionTankTank();
    CollisionPlayerEnemy();
    CollisionProjEnemy();
    CollisionPlayerBlocks();
    CollisionEnemiesBlocks();
    CollisionProjBlock(player.munitie);
    CollisionProjPlayer();

    if (player.getHp() <= 1 && !loser) {
        loser = true;
        cout << "Good luck next time, soldier!<3" << endl;
    }


    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(player.getTx(), player.getTy(), player.getTz()));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(player.getRotate()), glm::vec3(0, 1, 0));

        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
        RenderSimple(meshes["main_body"], shaders["LabShader"], modelMatrix,
                     glm::vec3((float) 253 / 255, (float) 146 / 255, (float) 87 / 255), player.getHp());
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(player.getTx(), player.getTy(), player.getTz()));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(player.getRotate()), glm::vec3(0, 1, 0));

        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
        RenderSimple(meshes["main_senile"], shaders["LabShader"], modelMatrix,
                     glm::vec3((float) 80 / 255, (float) 133 / 255, (float) 188 / 255), player.getHp());
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(player.getTx(), player.getTy(), player.getTz()));

        modelMatrix = glm::rotate(modelMatrix, RADIANS(player.getRotateTurela()), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
        RenderSimple(meshes["main_turela"], shaders["LabShader"], modelMatrix,
                     glm::vec3((float) 255 / 255, (float) 232 / 255, (float) 124 / 255), player.getHp());
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(player.getTx(), player.getTy(), player.getTz()));

        modelMatrix = glm::rotate(modelMatrix, RADIANS(player.getRotateTurela()), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
        RenderSimple(meshes["main_tun"], shaders["LabShader"], modelMatrix,
                     glm::vec3((float) 80 / 255, (float) 133 / 255, (float) 188 / 255), player.getHp());
        //   RenderMesh(meshes["munitie"], shaders["VertexNormal"], modelMatrix);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.01f, 0));
        // modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        RenderSimple(meshes["plane50"], shaders["LabShader"], modelMatrix,
                     glm::vec3((float) 176 / 255, (float) 139 / 255, (float) 232 / 255), 100);
    }
    for (auto &proj: player.munitie) {
        proj.setTtl(proj.getTtl() - deltaTimeSeconds);
        if (proj.getTtl() >= 0.0f && proj.isRender() && player.getHp() > 1) {
            proj.moveForward(2 * deltaTimeSeconds);
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(proj.getPx(), proj.getPy(), proj.getPz()));
            modelMatrix = glm::rotate(modelMatrix, RADIANS(proj.getRotate()), glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
            RenderSimple(meshes["munitie"], shaders["LabShader"], modelMatrix,
                         glm::vec3((float) 154 / 255, (float) 66 / 255, (float) 83 / 255), 100);

        }
    }
    for (auto &enemy: opponents) {
        CollisionProjBlock(enemy.munitie);
        enemy.setTimeSinceLastProj(enemy.getTimeSinceLastProj() + deltaTimeSeconds);
        if (enemy.getHp() <= 1) {
            continue;
        }
        for (auto &proj: enemy.munitie) {
            proj.setTtl(proj.getTtl() - deltaTimeSeconds);
            if (proj.getTtl() >= 0.0f && proj.isRender()) {
                proj.moveForward(2 * deltaTimeSeconds);
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(proj.getPx(), proj.getPy(), proj.getPz()));
                modelMatrix = glm::rotate(modelMatrix, RADIANS(proj.getRotate()), glm::vec3(0, 1, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
                RenderSimple(meshes["munitie"], shaders["LabShader"], modelMatrix,
                             glm::vec3((float) 154 / 255, (float) 66 / 255, (float) 83 / 255), 100);

            }
        }
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.0f, 0.0f, -2.572));
        // modelMatrix = glm::rotate(modelMatrix, RADIANS(player.getRotate()), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
        RenderSimple(meshes["bloc1"], shaders["LabShader"], modelMatrix, glm::vec3(0, 0.5, 0), 100);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-8.0f, 0.0f, -9));
        // modelMatrix = glm::rotate(modelMatrix, RADIANS(player.getRotate()), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
        RenderSimple(meshes["bloc1"], shaders["LabShader"], modelMatrix, glm::vec3(0, 0.5, 0), 100);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(4.0f, 0.0f, -9));
        // modelMatrix = glm::rotate(modelMatrix, RADIANS(player.getRotate()), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
        RenderSimple(meshes["bloc2"], shaders["LabShader"], modelMatrix, glm::vec3(0, 0.5, 0), 100);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-8.0f, 0.0f, 9));
        // modelMatrix = glm::rotate(modelMatrix, RADIANS(player.getRotate()), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
        RenderSimple(meshes["bloc1"], shaders["LabShader"], modelMatrix, glm::vec3(0, 0.5, 0), 100);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-5.0f, 0.0f, 2.572));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
        RenderSimple(meshes["bloc2"], shaders["LabShader"], modelMatrix,
                     glm::vec3((float) 80 / 255, (float) 133 / 255, (float) 188 / 255), 100);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-7.0f, 0.0f, 1));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
        RenderSimple(meshes["bloc3"], shaders["LabShader"], modelMatrix, glm::vec3(0, 0.5, 0), 100);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-10.0f, 0.0f, -4));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
        RenderSimple(meshes["bloc4"], shaders["LabShader"], modelMatrix,
                     glm::vec3((float) 80 / 255, (float) 133 / 255, (float) 188 / 255), 100);
    }
    RenderEnemy(deltaTimeSeconds);

}


void Tema2::FrameEnd() {
    DrawCoordinateSystem(camera1->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) {
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera1->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


void Tema2::OnInputUpdate(float deltaTime, int mods) {
    if (player.getHp() > 1 && gameTime < 60.0f) {
        float cameraSpeed = 0;
        if (window->KeyHold(GLFW_KEY_W)) {
            player.moveForward(deltaTime);
            camera1->position = glm::vec3(player.getTx() + 1.5f, player.getTy() + 0.58f, player.getTz());
            camera1->Set(camera1->position, glm::vec3(player.getTx(), player.getTy(), player.getTz()),
                         glm::vec3(0, 1, 0));
            camera1->RotateThirdPerson_OY(RADIANS(player.getRotate()));

        }
        if (window->KeyHold(GLFW_KEY_S)) {

            player.moveBackward(deltaTime);
            camera1->position = glm::vec3(player.getTx() + 1.5f, player.getTy() + 0.58f, player.getTz());
            camera1->Set(camera1->position, glm::vec3(player.getTx(), player.getTy(), player.getTz()),
                         glm::vec3(0, 1, 0));
            camera1->RotateThirdPerson_OY(RADIANS(player.getRotate()));
        }
        if (window->KeyHold(GLFW_KEY_A)) {

            player.rotateLeft(deltaTime);
            camera1->position = glm::vec3(player.getTx() + 1.5f, player.getTy() + 0.58f, player.getTz());
            camera1->Set(camera1->position, glm::vec3(player.getTx(), player.getTy(), player.getTz()),
                         glm::vec3(0, 1, 0));
            camera1->RotateThirdPerson_OY(RADIANS(player.getRotate()));

        }
        if (window->KeyHold(GLFW_KEY_D)) {
            player.rotateRight(deltaTime);
            camera1->position = glm::vec3(player.getTx() + 1.5f, player.getTy() + 0.58f, player.getTz());
            camera1->Set(camera1->position, glm::vec3(player.getTx(), player.getTy(), player.getTz()),
                         glm::vec3(0, 1, 0));
            camera1->RotateThirdPerson_OY(RADIANS(player.getRotate()));
        }
    }
}


void Tema2::OnKeyPress(int key, int mods) {
    // Add key press event
    if (key == GLFW_KEY_T) {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections
    if (key == GLFW_KEY_O) {
        projectionMatrix = glm::ortho(0.0f, width, 0.0f, height, 20.0f, -20.0f);
    }
    if (key == GLFW_KEY_P) {
        projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 200.0f);
    }

}

void Tema2::OnKeyRelease(int key, int mods) {

}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        // TODO(student): Rotate the camera in third-person mode around
        // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
        // variables for setting up the rotation speed.
        camera1->RotateThirdPerson_OX(sensivityOX * deltaY);
        camera1->RotateThirdPerson_OY(sensivityOY * deltaX);


    } else {
        player.setRotateTurela(player.getRotateTurela() + deltaX);
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button press event
    if (button == 1) {
        if (timeSinceLastProj >= 1.0f) {
            timeSinceLastProj = 0.0f;
            Proiectil proj = Proiectil(player.getTx(), player.getTy(), player.getTz(), player.getRotateTurela(), 2.0f,
                                       true);
            proj.setPx(player.getTx());
            proj.setPy(player.getTy());
            proj.setPz(player.getTz());
            player.munitie.push_back(proj);

        }
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
}


void Tema2::OnWindowResize(int width, int height) {
}
