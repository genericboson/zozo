extends Control

@onready var dropDown = $CharacterDropDown

func _physics_process(_delta: float) -> void:
	#dropDown.add_item()
	pass

func _on_back_button_pressed() -> void:
	get_tree().change_scene_to_file("res://scene/Lobby.tscn")

func _on_select_button_pressed() -> void:
	pass # Replace with function body.
	
func _add_characters(characters: Array) -> void:
	for character in characters:
		dropDown.add_item(character)

func _on_ready() -> void:
	dropDown.add_item("Choose your character")
	GDGlobal.game_socket_manager.SendCharacterListReq(Global.user_id, Global.token)
