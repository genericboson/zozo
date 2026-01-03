extends Control

@onready var dropDown = $CharacterDropDown

func _physics_process(_delta: float) -> void:
	#dropDown.add_item()
	pass

func _on_back_button_pressed() -> void:
	get_tree().change_scene_to_file("res://scene/Lobby.tscn")

func _on_select_button_pressed() -> void:
	var selectedCharacterId = dropDown.get_selected_id()
	GDGlobal.game_socket_manager.SendCharacterSelectReq(selectedCharacterId, GDGlobal.token)

func _select_character(_x: float, _y: float) -> void:
	get_tree().change_scene_to_file("res://scene/main.tscn")

func _add_characters(characters: Dictionary[int,String]) -> void:
	for key in characters:
		dropDown.add_item(characters[key], key)

func _on_ready() -> void:
	dropDown.add_item("Choose your character")
	GDGlobal.game_socket_manager.SendCharacterListReq(GDGlobal.user_id, GDGlobal.token)
