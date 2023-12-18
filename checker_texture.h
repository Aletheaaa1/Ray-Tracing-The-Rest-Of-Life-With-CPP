#pragma once
#include "solid_color.h"
#include "texture.h"

class CheckerTexture :public Texture
{
public:
	CheckerTexture() = default;
	CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);
	CheckerTexture(const vec3& c1, const vec3& c2);

	vec3 Value(double u, double v, const vec3& position) const override;

public:
	std::shared_ptr<Texture> odd, even;
};

inline CheckerTexture::CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd) :odd(std::move(odd)), even(std::move(even))
{
}

inline CheckerTexture::CheckerTexture(const vec3& c1, const vec3& c2) : odd(std::make_shared<SolidColor>(c1)), even(std::make_shared<SolidColor>(c2))
{
}

inline vec3 CheckerTexture::Value(double u, double v, const vec3& position) const
{
	auto sines = sin(10 * position.x()) * sin(10 * position.y()) * sin(10 * position.z());
	// 通过相乘sin值的结果符号来判断用哪个单色纹理的颜色
	if (sines < 0)
		return odd->Value(u, v, position);
	else
		return even->Value(u, v, position);
}
