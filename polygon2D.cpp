#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "scene.h"
#include "title.h"
#include "titleCamera.h"
#include "game.h"
#include "camera.h"


void Polygon2D::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal   = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(SCREEN_WIDTH, 0.0f, 0.0f);
	vertex[1].Normal   = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(0.0f, SCREEN_HEIGHT, 0.0f);
	vertex[2].Normal   = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	vertex[3].Normal   = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	
	//テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\texture\\sky.jpg", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, 
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, 
		"shader\\unlitTexturePS.cso");

}

void Polygon2D::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Polygon2D::Update()
{
	
}

void Polygon2D::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.5f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
	
	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	//ステンシル読込有効
	Renderer::SetStencilEnable(false);

	//ポリゴン設定
	Renderer::GetDeviceContext()->Draw(4, 0);


	Renderer::SetDepthEnable(true);

	SCENE_STATE scene = Scene::GetInstance()->GetNowScene()->GetSceneState();

	if (scene == SCENE_STATE::SCENE_TITLE) {
		Scene::GetInstance()->GetScene<Title>()->GetGameObject<TitleCamera>()->Draw();
	}
	else {
		Scene::GetInstance()->GetScene<Game>()->GetGameObject<Camera>()->Draw();
	}

}
