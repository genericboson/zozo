extends Node

var lobby_socket_manager = load("res://script/LobbySocketManager.cs").new()
var game_socket_manager = load("res://script/GameSocketManager.cs").new()

var account = ""
var token = ""
var user_id = 0
var game_server_ip = ""
var game_server_port = ""

# frame per second = 33.3
const SECOND_PER_FRAME = 0.03

func SendCharacterPositionUpdateReq(x:float, y:float, direction:int) -> void:
	game_socket_manager.SendCharacterPositionUpdateReq(x, y, direction)

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
