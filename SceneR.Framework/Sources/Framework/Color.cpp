// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Color.hpp>

#include <cassert>

#include <System/Math.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>

using namespace System;
using namespace SceneR::Framework;

const Color Color::AliceBlue        { 0xF0, 0xF8, 0xFF, 0xFF };
const Color Color::AntiqueWhite     { 0xFA, 0xEB, 0xD7, 0xFF };
const Color Color::Aqua             { 0x00, 0xFF, 0xFF, 0xFF };
const Color Color::Aquamarine       { 0x7F, 0xFF, 0xD4, 0xFF };
const Color Color::Azure            { 0xF0, 0xFF, 0xFF, 0xFF };
const Color Color::Beige            { 0xF5, 0xF5, 0xDC, 0xFF };
const Color Color::Bisque           { 0xFF, 0xE4, 0xC4, 0xFF };
const Color Color::Black            { 0x00, 0x00, 0x00, 0xFF };
const Color Color::BlanchedAlmond   { 0xFF, 0xEB, 0xCD, 0xFF };
const Color Color::Blue             { 0xFF, 0x00, 0x00, 0xFF };
const Color Color::BlueViolet       { 0x8A, 0x2B, 0xE2, 0xFF };
const Color Color::Brown            { 0xA5, 0x2A, 0x2A, 0xFF };
const Color Color::BurlyWood        { 0xDE, 0xB8, 0x87, 0xFF };
const Color Color::CadetBlue        { 0x5F, 0x9E, 0xA0, 0xFF };
const Color Color::Chartreuse       { 0x7F, 0xFF, 0x00, 0xFF };
const Color Color::Chocolate        { 0xD2, 0x69, 0x1E, 0xFF };
const Color Color::Coral            { 0xFF, 0x7F, 0x50, 0xFF };
const Color Color::CornflowerBlue   { 0x64, 0x95, 0xED, 0xFF };
const Color Color::Cornsilk         { 0xFF, 0xF8, 0xDC, 0xFF };
const Color Color::Crimson          { 0xDC, 0x14, 0x3C, 0xFF };
const Color Color::Cyan             { 0x00, 0xFF, 0xFF, 0xFF };
const Color Color::DarkBlue         { 0x00, 0x00, 0x8B, 0xFF };
const Color Color::DarkCyan         { 0x00, 0x8B, 0x8B, 0xFF };
const Color Color::DarkGoldenrod    { 0xB8, 0x86, 0x0B, 0xFF };
const Color Color::DarkGray         { 0xA9, 0xA9, 0xA9, 0xFF };
const Color Color::DarkGreen        { 0x00, 0x64, 0x00, 0xFF };
const Color Color::DarkKhaki        { 0xBD, 0xB7, 0x6B, 0xFF };
const Color Color::DarkMagenta      { 0x8B, 0x00, 0x8B, 0xFF };
const Color Color::DarkOliveGreen   { 0x55, 0x6B, 0x2F, 0xFF };
const Color Color::DarkOrange       { 0xFF, 0x8C, 0x00, 0xFF };
const Color Color::DarkOrchid       { 0x99, 0x32, 0xCC, 0xFF };
const Color Color::DarkRed          { 0x8B, 0x00, 0x00, 0xFF };
const Color Color::DarkSalmon       { 0xE9, 0x96, 0x7A, 0xFF };
const Color Color::DarkSeaGreen     { 0x8F, 0xBC, 0x8F, 0xFF };
const Color Color::DarkSlateBlue    { 0x48, 0x3D, 0x8B, 0xFF };
const Color Color::White            { 0xFF, 0xFF, 0xFF, 0xFF };

Color::Color()
    : Color ( 0.0f, 0.0f, 0.0f, 0.0f )
{
}

Color::Color(const Vector3& vector)
    : Color ( vector.X(), vector.Y(), vector.Z(), 1.0f )
{
}

Color::Color(const Vector4& vector)
    : Color ( vector.X(), vector.Y(), vector.Z(), vector.W() )
{
}

Color::Color(const float& r, const float& g, const float& b)
    : Color ( r, g, b, 1.0f )
{
}

Color::Color(const float& r, const float& g, const float& b, const float& a)
    : r { r }
    , g { g }
    , b { b }
    , a { a }
{
}

Color::Color(const Color& color)
    : r { color.r }
    , g { color.g }
    , b { color.b }
    , a { color.a }
{
}

Color::~Color()
{
}

float Color::R() const
{
    return this->r;
}

float Color::G() const
{
    return this->g;
}

float Color::B() const
{
    return this->b;
}

float Color::A() const
{
    return this->a;
}

uint32_t Color::PackedValue() const
{
    return ((static_cast<uint32_t>(this->r) * 255) << 24)
         + ((static_cast<uint32_t>(this->g) * 255) << 16)
         + ((static_cast<uint32_t>(this->b) * 255) << 8)
         +  (static_cast<uint32_t>(this->a) * 255);
}

float& Color::operator[](const std::size_t& index)
{
    assert(index < 4);

    return (this->color[index]);
}

const float& Color::operator[](const std::size_t& index) const
{
    assert(index >= 0 && index < 4);

    return (this->color[index]);
}

Color& Color::operator=(const Color& color)
{
    if (this != &color)
    {
        this->r = color.r;
        this->g = color.g;
        this->b = color.b;
        this->a = color.a;
    }

    return *this;
}

bool Color::operator==(const Color& color) const
{
    return (Math::Equal(this->r, color.r)
         && Math::Equal(this->g, color.g)
         && Math::Equal(this->b, color.b)
         && Math::Equal(this->a, color.a));
}

bool Color::operator!=(const Color& color) const
{
    return !(*this == color);
}

Color& Color::operator*=(const Color& color)
{
    this->r *= color.r;
    this->g *= color.g;
    this->b *= color.b;
    this->a *= color.a;

    return *this;
}

Color& Color::operator*=(const float& value)
{
    this->r *= value;
    this->g *= value;
    this->b *= value;
    this->a *= value;

    return *this;
}

Color& Color::operator-=(const Color& color)
{
    this->r -= color.r;
    this->g -= color.g;
    this->b -= color.b;
    this->a -= color.a;

    return *this;
}

Color& Color::operator+=(const Color& color)
{
    this->r += color.r;
    this->g += color.g;
    this->b += color.b;
    this->a += color.a;

    return *this;
}

const Color Color::operator*(const Color& color) const
{
    auto result = *this;

    result *= color;

    return result;
}

const Color Color::operator*(const float& value) const
{
    auto result = *this;

    result *= value;

    return result;
}

const Color Color::operator-(const Color& color) const
{
    auto result = *this;

    result -= color;

    return result;
}

const Color Color::operator+(const Color& color) const
{
    auto result = *this;

    result += color;

    return result;
}
