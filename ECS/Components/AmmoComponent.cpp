#pragma once

struct AmmoComponent {
	int clip_size;
	int current_clip;

	int reserve_size;
	int current_reserve;

	int reload_time;
	bool is_reloading;
	int reload_progress;
};