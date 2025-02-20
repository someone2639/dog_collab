#include "src/game/envfx_snow.h"

const GeoLayout warpbox_diamondfacescube[] = {
	GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 250, 0, 0, 0, 0),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 100, 0, warpbox_switchopt_root_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout warpbox_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, warpbox_root_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, warpbox_root_mesh_layer_4),
			GEO_ASM(0, geo_warp_box_scale),
			GEO_SCALE(LAYER_OPAQUE, 65536),
			GEO_OPEN_NODE(),
				GEO_SWITCH_CASE(0, geo_switch_anim_state),
				GEO_OPEN_NODE(),
					GEO_NODE_START(),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 125, 0, warpbox_diamond_faces_mesh_layer_1),
					GEO_CLOSE_NODE(),
					GEO_BRANCH(1, warpbox_diamondfacescube),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, warpbox_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, warpbox_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
