const Collision balloon_platform_bits_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(8),
	COL_VERTEX(-168, -91, 192),
	COL_VERTEX(-168, 0, 192),
	COL_VERTEX(-188, 0, -168),
	COL_VERTEX(-188, -91, -168),
	COL_VERTEX(172, 0, -188),
	COL_VERTEX(172, -91, -188),
	COL_VERTEX(192, 0, 172),
	COL_VERTEX(192, -91, 172),
	COL_TRI_INIT(SURFACE_DEFAULT, 12),
	COL_TRI(0, 1, 2),
	COL_TRI(0, 2, 3),
	COL_TRI(3, 2, 4),
	COL_TRI(3, 4, 5),
	COL_TRI(5, 4, 6),
	COL_TRI(5, 6, 7),
	COL_TRI(7, 6, 1),
	COL_TRI(7, 1, 0),
	COL_TRI(3, 5, 7),
	COL_TRI(3, 7, 0),
	COL_TRI(4, 2, 1),
	COL_TRI(4, 1, 6),
	COL_TRI_STOP(),
	COL_END()
};
