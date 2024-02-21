#pragma once

#include "components/simple_scene.h"
#include "Player.h"
#include "Proiectil.h"
//#include "Enemy.h"
#include "Tank.h"
#include "Building.h"
#include "Tank.h"
#include "lab_m1/tema2/camera.h"
#include "components/transform.h"
#include "components/simple_scene.h"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();
        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;
        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(1));
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;


    protected:
        //implemented::Camera *camera;
        void RenderEnemy(float deltatime);

        void CollisionProjEnemy();

        void CollisionTankTank();

        void CollisionPlayerEnemy();

        void CollisionPlayerBlocks();

        //void CollisionProjBlock();

        void EnemyAttack();
        implemented::Camera1 *camera1;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        //Player player = Player(0.0f,0.58f,0.0f, -90.0f);
        // TODO(student): If you need any other class variables, define them here.
        float fov;
        float height, width;
        int k;
        float tx, tz;
        float timeSinceLastProj;
        float ttl;
        float gameTime;
        float sum;
        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;
        float hp;

        void CollisionEnemiesBlocks();

        void CollisionProjBlock(vector<Proiectil> v);

        void CollisionProjPlayer();

        void
        RenderSimple(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color, float hp);
        bool loser;
        int score;
        float winner;
    };
}   // namespace m1
