#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("sample.png");
	sprite_ = Sprite::Create(textureHandle_, {100,50});
	modeltextureHandle_ = TextureManager::Load("sample.png");
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	//サウンドデータの読み込み
	soundDateHandle_ = audio_->LoadWave("fanfare.wav");
	//音声再生
	audio_->PlayWave(soundDateHandle_);
	//音声再生
	voiceHandle_ = audio_->PlayWave(soundDateHandle_,true);
}

void GameScene::Update() { 
	//スプライトの今の座標を取得
	Vector2 position = sprite_->GetPosition();
	//座標を｛2，1｝移動
	position.x += 2.0f;
	position.y += 1.0f;
	//移動した座標をスプライトに反映	
	sprite_->SetPosition(position);
	//スペースキーを押した瞬間
	if (input_->TriggerKey(DIK_SPACE)) {
		//音声停止
		audio_->StopWave(voiceHandle_);
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	/// 3Dモデル描画
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
