#include "TextureManager.h"
#include <exception>

//
using std::string;
using std::make_unique;
using std::move;
using sf::Texture;

namespace game {
	TextureManager::TextureManager()
	{
	}

	void TextureManager::load(string id, string file_path)
	{
		auto it = texture_data_.find(id);
		if (it == texture_data_.end()) {

			auto texture = make_unique<Texture>();
			texture->loadFromFile(file_path);

			texture_data_.insert({ id, move(texture) });
		}
		else {
			throw std::exception("failed to find file");
		}
	}

	void TextureManager::remove(string id)
	{
		auto it = texture_data_.find(id);
		if (it != texture_data_.end()) {
			texture_data_.erase(id);
		}
		else {
			throw std::exception("id not found");
		}
	}

	const Texture& TextureManager::get(string id) const
	{
		auto it = texture_data_.find(id);

		if (it != texture_data_.end()) {
			return *it->second;
		}

		// empty texture
		return Texture();
	}
}