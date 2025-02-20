void scroll_sts_mat_wf_dl_barrier() {
	Gfx *mat = segmented_to_virtual(mat_wf_dl_barrier);
	shift_t(mat, 12, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_wf_dl_backdrop_water_layer5() {
	Gfx *mat = segmented_to_virtual(mat_wf_dl_backdrop_water_layer5);
	shift_t(mat, 15, PACK_TILESIZE(0, 3));
	shift_s(mat, 23, PACK_TILESIZE(0, 1));
	shift_t(mat, 23, PACK_TILESIZE(0, 4));
};

void scroll_sts_mat_wf_dl_atoll_water_layer7() {
	Gfx *mat = segmented_to_virtual(mat_wf_dl_atoll_water_layer7);
	shift_t(mat, 13, PACK_TILESIZE(0, 3));
	shift_s(mat, 21, PACK_TILESIZE(0, 1));
	shift_t(mat, 21, PACK_TILESIZE(0, 4));
};

void scroll_sts_mat_wf_dl_ground_lava_layer1() {
	Gfx *mat = segmented_to_virtual(mat_wf_dl_ground_lava_layer1);
	shift_t(mat, 20, PACK_TILESIZE(0, 1));
	shift_s(mat, 35, PACK_TILESIZE(0, 1));
	shift_t(mat, 35, PACK_TILESIZE(0, 2));
};

void scroll_sts_mat_wf_dl_flowing_lava_layer1() {
	Gfx *mat = segmented_to_virtual(mat_wf_dl_flowing_lava_layer1);
	shift_t(mat, 20, PACK_TILESIZE(0, 1));
	shift_t(mat, 35, PACK_TILESIZE(0, 2));
};

void scroll_wf() {
	scroll_sts_mat_wf_dl_barrier();
	scroll_sts_mat_wf_dl_backdrop_water_layer5();
	scroll_sts_mat_wf_dl_atoll_water_layer7();
	scroll_sts_mat_wf_dl_ground_lava_layer1();
	scroll_sts_mat_wf_dl_flowing_lava_layer1();
}
