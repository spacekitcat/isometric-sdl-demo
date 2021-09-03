#ifndef CACHEDTEXTRENDERER_H
#define CACHEDTEXTRENDERER_H

#include "../text/text-renderer.hpp"

class CachedTextRenderer  
{
	private:
		TextRenderer &_textRenderer;
	public:

		CachedTextRenderer(TextRenderer &textRenderer);
		~CachedTextRenderer();

        std::shared_ptr<TextureWrapper> renderText(std::string text, std::pair<float, float> position);
};
#endif