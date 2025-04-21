#pragma once
#include "gameObject.h"

#define FIELDHIGHT_NUM (35)

class MeshField : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};


	VERTEX_3D m_Vertex[FIELDHIGHT_NUM][FIELDHIGHT_NUM];


public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	float GetHeight(XMFLOAT3 pos);

};