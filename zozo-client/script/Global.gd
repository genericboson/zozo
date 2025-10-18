extends Node

var socket_manager = load("res://script/SocketManager.cs").new()
var socketTimer = Timer.new()



func message_box(text: String, title: String='Message') -> void:
	var dialog = AcceptDialog.new()
	dialog.dialog_text = text
	dialog.title = title
	dialog.get_label().horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	var screenSize = DisplayServer.screen_get_size()
	dialog.set_size(Vector2i(screenSize.x/4,0))
	
	var scene_tree = Engine.get_main_loop()
	scene_tree.current_scene.add_child(dialog)
	dialog.popup_centered()
