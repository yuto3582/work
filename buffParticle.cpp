#include "manager.h"
#include "scene.h"
#include "camera.h"
#include "buffParticle.h"
#include "game.h"
#include "transform2DComponent.h"

void BuffParticle::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 0.2f, 0.2f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 0.2f, 0.2f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 0.2f, 0.2f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 0.2f, 0.2f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	AddComponent<Transform2DComponent>()->AddTextureData(L"asset\\texture\\particle.png");
	GetComponent<Transform2DComponent>()->SetVertex(vertex);
	GetComponent<Transform2DComponent>()->SetBillBoard(true);
	GetComponent<Transform2DComponent>()->SetZBuff(true);
	GetComponent<Transform2DComponent>()->SetScale(XMFLOAT3(0.1f, 0.5f, 0.1f));

	for (auto component : m_ComponentList)
	{
		component->Init();
	}
}

void BuffParticle::Uninit()
{
	for (auto component : m_ComponentList)
	{
		component->Uninit();
		delete component;
	}
}

void BuffParticle::Update()
{
	if (m_isPlayerBuff)
	{
		//パーティクル発射
		for (int i = 0; i < PARTICLE_MAX; i++) 
		{
			if (!m_Particle[i].Enable) 
			{
				m_Particle[i].Enable = true;

				m_Particle[i].Pos = GetComponent<Transform2DComponent>()->GetPos();
				m_Particle[i].Vel.y = (rand() % 100 + 50) / 8000.0f;

				m_Particle[i].Life = 90;

				break;
			}
		}
		for (int i = 0; i < PARTICLE_MAX; i++) 
		{
			if (m_Particle[i].Enable) 
			{
				m_Particle[i].Pos.y += m_Particle[i].Vel.y;
				m_Particle[i].Pos.x += (rand() % 100 - 50) / 650.0f;
				m_Particle[i].Pos.z += (rand() % 100 - 50) / 650.0f;
				m_Particle[i].Life--;

				if (m_Particle[i].Life < 0) {
					m_Particle[i].Enable = false;
				}
			}
		}
	}

}

void BuffParticle::Draw()
{
	if (m_isPlayerBuff)
	{
		for (int i = 0; i < PARTICLE_MAX; i++)
		{
			if (m_Particle[i].Enable)
			{
				for (auto component : m_ComponentList)
				{
					GetComponent<Transform2DComponent>()->SetPos(m_Particle[i].Pos);
					component->Draw();
				}
			}
		}
	}
}
