extends Control

signal insert_to_dropdown(characterName: String)

@onready var dropDown = $CharacterDropDown

func _physics_process(_delta: float) -> void:
	#dropDown.add_item()
	pass

func _on_insert_to_dropdown(characterName: String) -> void:
	dropDown.add_item(characterName)
