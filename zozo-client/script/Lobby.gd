extends Control

@onready var accountInput = $AccountInput
@onready var passwordInput = $PasswordInput

@onready var dropDown = $CharacterDropDown

func _on_button_pressed() -> void:
	Global.socket_manager.SendLogin(accountInput.text,passwordInput.text)
	#get_tree().change_scene_to_file("res://scene/CharacterSelect.tscn")
	
func _on_setting_pressed() -> void:
	Global.message_box("개발 예정...")

func _test(password: String) -> void:
	print(password)
	#dropDown.add_item(password)
