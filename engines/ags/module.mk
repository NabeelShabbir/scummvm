MODULE := engines/ags

MODULE_OBJS = \
	ags.o \
	events.o \
	game_scanner.o \
	globals.o \
	metaengine.o \
	music.o \
	console.o \
	lib/aastr-0.1.1/aarot.o \
	lib/aastr-0.1.1/aastr.o \
	lib/aastr-0.1.1/aautil.o \
	lib/alfont/alfont.o \
	lib/allegro/col_blend.o \
	lib/allegro/color.o \
	lib/allegro/config.o \
	lib/allegro/draw.o \
	lib/allegro/file.o \
	lib/allegro/fixed.o \
	lib/allegro/flood.o \
	lib/allegro/gfx.o \
	lib/allegro/graphics.o \
	lib/allegro/math.o \
	lib/allegro/rotate.o \
	lib/allegro/surface.o \
	lib/allegro/system.o \
	lib/allegro/unicode.o \
	lib/hq2x/hq2x3x.o \
	lib/std/std.o \
	lib/system/datetime.o \
	shared/ac/dynobj/script_audio_clip.o \
	shared/ac/audio_clip_type.o \
	shared/ac/character_info.o \
	shared/ac/common.o \
	shared/ac/dialog_topic.o \
	shared/ac/game_setup_struct.o \
	shared/ac/game_setup_struct_base.o \
	shared/ac/inventory_item_info.o \
	shared/ac/keycode.o \
	shared/ac/mouse_cursor.o \
	shared/ac/sprite_cache.o \
	shared/ac/view.o \
	shared/ac/words_dictionary.o \
	shared/core/asset.o \
	shared/core/asset_manager.o \
	shared/debugging/debug_manager.o \
	shared/font/fonts.o \
	shared/font/ttf_font_renderer.o \
	shared/font/wfn_font.o \
	shared/font/wfn_font_renderer.o \
	shared/game/custom_properties.o \
	shared/game/interactions.o \
	shared/game/main_game_file.o \
	shared/game/room_file.o \
	shared/game/room_file_base.o \
	shared/game/room_file_deprecated.o \
	shared/game/room_struct.o \
	shared/game/tra_file.o \
	shared/gfx/allegro_bitmap.o \
	shared/gfx/bitmap.o \
	shared/gfx/image.o \
	shared/gui/gui_button.o \
	shared/gui/gui_inv.o \
	shared/gui/gui_label.o \
	shared/gui/gui_listbox.o \
	shared/gui/gui_main.o \
	shared/gui/gui_object.o \
	shared/gui/gui_slider.o \
	shared/gui/gui_textbox.o \
	shared/script/cc_error.o \
	shared/script/cc_options.o \
	shared/script/cc_script.o \
	shared/util/aligned_stream.o \
	shared/util/buffered_stream.o \
	shared/util/compress.o \
	shared/util/data_stream.o \
	shared/util/directory.o \
	shared/util/file.o \
	shared/util/file_stream.o \
	shared/util/geometry.o \
	shared/util/ini_file.o \
	shared/util/ini_util.o \
	shared/util/lzw.o \
	shared/util/misc.o \
	shared/util/memory_stream.o \
	shared/util/multi_file_lib.o \
	shared/util/path.o \
	shared/util/proxy_stream.o \
	shared/util/stdio_compat.o \
	shared/util/stream.o \
	shared/util/string.o \
	shared/util/string_compat.o \
	shared/util/string_utils.o \
	shared/util/text_stream_reader.o \
	shared/util/text_stream_writer.o \
	shared/util/version.o \
	shared/util/wgt2_allg.o \
	engine/ac/audio_channel.o \
	engine/ac/audio_clip.o \
	engine/ac/button.o \
	engine/ac/cd_audio.o \
	engine/ac/character.o \
	engine/ac/character_extras.o \
	engine/ac/character_info_engine.o \
	engine/ac/date_time.o \
	engine/ac/dialog.o \
	engine/ac/dialog_options_rendering.o \
	engine/ac/display.o \
	engine/ac/draw.o \
	engine/ac/drawing_surface.o \
	engine/ac/draw_software.o \
	engine/ac/dynamic_sprite.o \
	engine/ac/event.o \
	engine/ac/file.o \
	engine/ac/game.o \
	engine/ac/game_setup.o \
	engine/ac/game_state.o \
	engine/ac/global_api.o \
	engine/ac/global_audio.o \
	engine/ac/global_button.o \
	engine/ac/global_character.o \
	engine/ac/global_date_time.o \
	engine/ac/global_debug.o \
	engine/ac/global_dialog.o \
	engine/ac/global_display.o \
	engine/ac/global_drawing_surface.o \
	engine/ac/global_dynamic_sprite.o \
	engine/ac/global_file.o \
	engine/ac/global_game.o \
	engine/ac/global_gui.o \
	engine/ac/global_hotspot.o \
	engine/ac/global_inventory_item.o \
	engine/ac/global_inv_window.o \
	engine/ac/global_label.o \
	engine/ac/global_listbox.o \
	engine/ac/global_mouse.o \
	engine/ac/global_object.o \
	engine/ac/global_overlay.o \
	engine/ac/global_palette.o \
	engine/ac/global_parser.o \
	engine/ac/global_record.o \
	engine/ac/global_region.o \
	engine/ac/global_room.o \
	engine/ac/global_screen.o \
	engine/ac/global_slider.o \
	engine/ac/global_string.o \
	engine/ac/global_textbox.o \
	engine/ac/global_timer.o \
	engine/ac/global_translation.o \
	engine/ac/global_video.o \
	engine/ac/global_viewport.o \
	engine/ac/global_view_frame.o \
	engine/ac/global_walkable_area.o \
	engine/ac/global_walk_behind.o \
	engine/ac/gui.o \
	engine/ac/gui_control.o \
	engine/ac/gui_inv.o \
	engine/ac/hotspot.o \
	engine/ac/interface_button.o \
	engine/ac/interface_element.o \
	engine/ac/inventory_item.o \
	engine/ac/inv_window.o \
	engine/ac/label.o \
	engine/ac/listbox.o \
	engine/ac/math.o \
	engine/ac/mouse.o \
	engine/ac/move_list.o \
	engine/ac/object.o \
	engine/ac/overlay.o \
	engine/ac/parser.o \
	engine/ac/properties.o \
	engine/ac/region.o \
	engine/ac/rich_game_media.o \
	engine/ac/room.o \
	engine/ac/room_object.o \
	engine/ac/room_status.o \
	engine/ac/route_finder.o \
	engine/ac/route_finder_impl.o \
	engine/ac/route_finder_impl_legacy.o \
	engine/ac/route_finder_jps.o \
	engine/ac/screen.o \
	engine/ac/screen_overlay.o \
	engine/ac/script_containers.o \
	engine/ac/slider.o \
	engine/ac/speech.o \
	engine/ac/sprite.o \
	engine/ac/sprite_cache_engine.o \
	engine/ac/string.o \
	engine/ac/system.o \
	engine/ac/sys_events.o \
	engine/ac/textbox.o \
	engine/ac/timer.o \
	engine/ac/translation.o \
	engine/ac/view_frame.o \
	engine/ac/viewport_script.o \
	engine/ac/walkable_area.o \
	engine/ac/walk_behind.o \
	engine/ac/dynobj/cc_ags_dynamic_object.o \
	engine/ac/dynobj/cc_audio_channel.o \
	engine/ac/dynobj/cc_audio_clip.o \
	engine/ac/dynobj/cc_character.o \
	engine/ac/dynobj/cc_dialog.o \
	engine/ac/dynobj/cc_dynamic_array.o \
	engine/ac/dynobj/cc_dynamic_object.o \
	engine/ac/dynobj/cc_gui.o \
	engine/ac/dynobj/cc_gui_object.o \
	engine/ac/dynobj/cc_hotspot.o \
	engine/ac/dynobj/cc_inventory.o \
	engine/ac/dynobj/cc_object.o \
	engine/ac/dynobj/cc_region.o \
	engine/ac/dynobj/cc_serializer.o \
	engine/ac/dynobj/managed_object_pool.o \
	engine/ac/dynobj/script_camera.o \
	engine/ac/dynobj/script_date_time.o \
	engine/ac/dynobj/script_dialog_options_rendering.o \
	engine/ac/dynobj/script_dict.o \
	engine/ac/dynobj/script_drawing_surface.o \
	engine/ac/dynobj/script_dynamic_sprite.o \
	engine/ac/dynobj/script_file.o \
	engine/ac/dynobj/script_overlay.o \
	engine/ac/dynobj/script_set.o \
	engine/ac/dynobj/script_string.o \
	engine/ac/dynobj/script_user_object.o \
	engine/ac/dynobj/script_viewport.o \
	engine/ac/dynobj/script_view_frame.o \
	engine/ac/statobj/ags_static_object.o \
	engine/ac/statobj/static_array.o \
	engine/debugging/console_output_target.o \
	engine/debugging/debug.o \
	engine/debugging/file_based_ags_debugger.o \
	engine/debugging/log_file.o \
	engine/debugging/message_buffer.o \
	engine/device/mouse_w32.o \
	engine/font/fonts_engine.o \
	engine/game/game_init.o \
	engine/game/savegame.o \
	engine/game/savegame_components.o \
	engine/game/savegame_v321.o \
	engine/game/viewport.o \
	engine/gfx/ali_3d_scummvm.o \
	engine/gfx/blender.o \
	engine/gfx/color_engine.o \
	engine/gfx/gfx_driver_base.o \
	engine/gfx/gfx_driver_factory.o \
	engine/gfx/gfx_util.o \
	engine/gfx/gfxfilter_scaling.o \
	engine/gfx/gfxfilter_scummvm_renderer.o \
	engine/gui/animating_gui_button.o \
	engine/gui/csci_dialog.o \
	engine/gui/gui_dialog.o \
	engine/gui/gui_engine.o \
	engine/gui/my_label.o \
	engine/gui/my_listbox.o \
	engine/gui/my_push_button.o \
	engine/gui/my_textbox.o \
	engine/gui/new_control.o \
	engine/main/config.o \
	engine/main/engine.o \
	engine/main/engine_setup.o \
	engine/main/game_file.o \
	engine/main/game_run.o \
	engine/main/game_start.o \
	engine/main/graphics_mode.o \
	engine/main/main.o \
	engine/main/quit.o \
	engine/main/update.o \
	engine/media/audio/ambient_sound.o \
	engine/media/audio/audio.o \
	engine/media/audio/clip_my_midi.o \
	engine/media/audio/queued_audio_item.o \
	engine/media/audio/sound.o \
	engine/media/audio/sound_clip.o \
	engine/media/video/video.o \
	engine/platform/base/ags_platform_driver.o \
	engine/platform/base/sys_main.o \
	engine/platform/scummvm/scummvm_platform_driver.o \
	engine/script/cc_instance.o \
	engine/script/executing_script.o \
	engine/script/exports.o \
	engine/script/runtime_script_value.o \
	engine/script/script.o \
	engine/script/script_api.o \
	engine/script/script_engine.o \
	engine/script/script_runtime.o \
	engine/script/system_imports.o \
	plugins/ags_plugin.o \
	plugins/ags_plugin.o \
	plugins/plugin_base.o \
	plugins/plugin_object_reader.o \
	plugins/ags_agi/ags_agi.o \
	plugins/ags_blend/ags_blend.o \
	plugins/ags_controller/ags_controller.o \
	plugins/ags_creditz/ags_creditz.o \
	plugins/ags_creditz/ags_creditz1.o \
	plugins/ags_creditz/ags_creditz2.o \
	plugins/ags_creditz/drawing.o \
	plugins/ags_fire/ags_fire.o \
	plugins/ags_flashlight/ags_flashlight.o \
	plugins/ags_galaxy_steam/ags_wadjeteye_steam.o \
	plugins/ags_galaxy_steam/ags_galaxy_steam.o \
	plugins/ags_joy/ags_joy.o \
	plugins/ags_nickenstien_gfx/ags_nickenstien_gfx.o \
	plugins/ags_pal_render/ags_pal_render.o \
	plugins/ags_pal_render/raycast.o \
	plugins/ags_parallax/ags_parallax.o \
	plugins/ags_snow_rain/ags_snow_rain.o \
	plugins/ags_snow_rain/weather.o \
	plugins/ags_sprite_font/ags_sprite_font.o \
	plugins/ags_sprite_font/ags_sprite_font_clifftop.o \
	plugins/ags_sprite_font/character_entry.o \
	plugins/ags_sprite_font/color.o \
	plugins/ags_sprite_font/sprite_font.o \
	plugins/ags_sprite_font/sprite_font_renderer.o \
	plugins/ags_sprite_font/sprite_font_renderer_clifftop.o \
	plugins/ags_sprite_font/variable_width_font.o \
	plugins/ags_sprite_font/variable_width_sprite_font.o \
	plugins/ags_sprite_font/variable_width_sprite_font_clifftop.o \
	plugins/ags_shell/ags_shell.o \
	plugins/ags_tcp_ip/ags_tcp_ip.o \
	plugins/ags_wadjet_util/ags_wadjet_util.o

ifdef ENABLE_AGS_TESTS
MODULE_OBJS += \
	tests/test_all.o \
	tests/test_file.o \
	tests/test_gfx.o \
	tests/test_inifile.o \
	tests/test_math.o \
	tests/test_memory.o \
	tests/test_sprintf.o \
	tests/test_string.o \
	tests/test_version.o
endif

# This module can be built as a plugin
ifeq ($(ENABLE_AGS), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk

# Detection objects
DETECT_OBJS += $(MODULE)/detection.o
