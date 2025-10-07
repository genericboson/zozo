extends Control



func _on_button_pressed() -> void:
	print("button pressed")
	get_tree().change_scene_to_file("res://scene/CharacterSelect.tscn")


func _on_setting_pressed() -> void:
	Global.message_box("개발 예정...")
