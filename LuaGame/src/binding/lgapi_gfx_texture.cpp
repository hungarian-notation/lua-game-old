#include "lgapi_gfx.h"

using namespace luagame;

void luagame_pushtexture(lua_State * L, std::shared_ptr<luagame::texture_object> texture) {
	luagame_pushobj<texture_object>(L, texture);
}

int lgapi_create_texture(lua_State * L) {
	const char * filename = luaL_checkstring(L, 1);
	auto tex = luagame_getcontext(L)->texture_cache[filename];
	luagame_pushtexture(L, tex);
	return 1;
}