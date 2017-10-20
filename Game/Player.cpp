#include "Player.hpp"

namespace Game_n {
	Player::Player(uint64_t client, std::string pseudo)
		: mClient(client)
		, mPseudo(pseudo)
	{

	}

	Player::~Player() {

	}

	Enums::Races Player::getRace() const
	{
		return mRace;
	}

	std::string Player::getPseudo() const
	{
		return mPseudo;
	}

	Game * Player::getGame() const
	{
		return mGame;
	}

	void Player::setPseudo(std::string pseudo)
	{
		mPseudo = pseudo;
	}

	void Player::setRace(Enums::Races race)
	{
		mRace = race;
	}

	void Player::setColor(Enums::Colors color)
	{
		mColor = color;
	}

	void Player::setClient(uint64_t client)
	{
		mClient = client;
	}

	void Player::setGame(Game * g)
	{
		mGame = g;
	}

	uint64_t Game_n::Player::getClient() const
	{
		return uint64_t();
	}

	Enums::Colors Player::getColor() const
	{
		return mColor;
	}
}