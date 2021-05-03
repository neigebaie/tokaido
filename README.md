# Tokaido 🎲
Adaptation du jeu de société Tokaido en langage C avec l'aide de la SDL (version 2.0.14).

## Liste des fonctionnalités à ajouter :
- jeu de base
- jeu en réseau
- IA pour pouvoir jouer contre l'ordi
- peut-être les DLC

## Compilation

| Dependence | URL |
| ------ | ------ |
| SDL 2.0 | https://www.libsdl.org/ |
| SDL_image 2.0  |  https://www.libsdl.org/projects/SDL_image/ |
| SDL_ttf 2.0  |  https://www.libsdl.org/projects/SDL_ttf/ |
| SDL_net 2.0  |  https://www.libsdl.org/projects/SDL_net/ |

Pour Arch

```bash
$ pacman -S sdl2 sdl2_image sdl2_mixer sdl2_net sdl2_ttf --needed
```

Pour Debian
```bash
$ apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev
```

### Linux
Pour compiler le projet, il suffit simplement d'utiliser la commande `make` et le tour est joué !
```bash
make
```

## Informations

Une grande partie des assets utilisés pour ce projet proviennent du jeu Steam Tokaido.
Si vous aimez le jeu, achetez la version Steam pour soutenir les développeurs ainsi que les créateurs du jeu.

[Lien vers le magasin Steam](https://store.steampowered.com/app/648750/Tokaido/)

[Jeu de plateau](https://www.philibertnet.com/fr/funforge/20177-tokaido-3770001556604.html)
