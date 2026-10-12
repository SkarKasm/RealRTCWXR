//
// RealRTCW XR: RealRTCW 5.4 bakes arms and gloves into the first-person weapon
// models ('hqarm' and 'hqhand' surfaces). In VR they move with the weapon, not the
// controllers, and XR already draws its own off-hand, so draw nothing.
//
models/weapons/hands/sleeve_default
{
	surfaceparm nodraw
	surfaceparm nomarks
	surfaceparm nolightmap
}

models/weapons/hands/glove_default
{
	surfaceparm nodraw
	surfaceparm nomarks
	surfaceparm nolightmap
}
