# Mythic

Mythic is a C++/C# - powered RPG framework designed to bring rich gameplay systems into your project with ease. It provides core features such as stats, abilities, inventory management, damage handling, and flexible stat modifiers - all built with seamless Blueprint / Unity VS integration in mind, so you can extend and customize systems with ease.


## Authors

- [@JamesMillsDev](https://github.com/JamesMillsDev)


## Features

- Dynamic Attribute System
    - Modifiers
    - Integer / Float type (configurable)
    - Damage Application
- Inventory
- Abilities
- Blueprint / Unity Visual Scripting Friendly


## Contributing

Contributions are welcome. If you find a bug or want to propose a feature, please open an issue first so it can be discussed before any work begins.

When submitting a pull request:

- Keep changes focused and minimal in scope
- Follow the existing code style and naming conventions
- Ensure Blueprint compatibility is preserved for any new systems
- Include a clear description of what the change does and why

For significant architectural changes, open a discussion issue before writing code to avoid wasted effort.


## FAQ

**Does Mythic require any third-party plugins?**
No. Mythic is self-contained and only depends on standard Unreal Engine modules.

**Can I use Mythic in a Blueprint-only project?**
The framework is written in C++ but is designed with Blueprint exposure as a priority. Most systems can be configured and extended without writing any C++.

**Is there a Unity version of Mythic?**
Yes. Mythic also supports Unity. The Unity version is designed to work with C# and integrates with Unity’s scripting environment, including compatibility with Unity Visual Scripting (node-based workflows).

**What version of Unreal Engine / Unity is supported?**
Check the releases page for the minimum supported engine version. Older versions are not guaranteed to be compatible.

**Can I mix Integer and Float attribute types in the same project?**
Yes. The attribute type is configurable per attribute, so you can use whichever precision suits each stat.

**How do I report a bug?**
Open an issue on GitHub with a clear description of the problem, steps to reproduce it, and the engine version you are using.


## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.


## Acknowledgements

- [Claude](https://claude.ai) - For description and detailed readme generation
- [Readme.so](https://readme.so) - For initial readme generation
