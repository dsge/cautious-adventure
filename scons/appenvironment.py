
import urllib.request
import os
import zipfile
import shutil
import json

editorDirectory = os.path.join(os.path.dirname(
    os.path.realpath(__file__)), '..', 'godot-editor')
last_version_filename = "last_downloaded_version.json"


def ensure_godot_binaries(version='4.2', suffix='stable'):
    force = needs_fresh_download(version, suffix)
    did_download = False
    if (ensure_binary(version, suffix, 'linux.x86_64', force)):
        did_download = True
    if (ensure_binary(version, suffix, 'win64.exe', force)):
        did_download = True
    if (did_download):
        update_last_downloaded_version(version, suffix)
    ensure_godot_selfcontained_mode()
    ensure_godot_editor_project()


def ensure_binary(version, suffix, platformBinaryName, force):
    binaryName = "Godot_v{version}-{suffix}_{platformBinaryName}".format(
        version=version, suffix=suffix, platformBinaryName=platformBinaryName)
    targetBinaryName = "Godot_{platformBinaryName}".format(
        platformBinaryName=platformBinaryName)
    finalEditorPath = os.path.abspath(
        os.path.join(editorDirectory, targetBinaryName))

    if (not os.path.isfile(finalEditorPath) or force):
        print("Downloading fresh {platformBinaryName} Godot Editor binary to '<project_root>/godot-editor'...".format(
            platformBinaryName=platformBinaryName))
        url = "https://downloads.tuxfamily.org/godotengine/{version}/{binaryName}.zip".format(
            version=version, binaryName=binaryName)
        local_tmp_filename, headers = urllib.request.urlretrieve(url)
        with zipfile.ZipFile(local_tmp_filename, "r") as zip_ref:
            extractDirectory = os.path.dirname(local_tmp_filename)
            zip_ref.extractall(extractDirectory)
            shutil.move(os.path.join(extractDirectory,
                        binaryName), finalEditorPath)
            if not os.name == 'nt':
                os.chmod(finalEditorPath, 0o744)

            return True
    return False


def needs_fresh_download(version, suffix):
    filename = os.path.join(editorDirectory, last_version_filename)
    if not os.path.isfile(filename):
        return True
    with open(filename) as f:
        data = json.load(f)
        return data['version'] != version or data['suffix'] != suffix


def update_last_downloaded_version(version, suffix):
    filename = os.path.join(editorDirectory, last_version_filename)
    dict = {
        'version': version,
        'suffix': suffix
    }
    with open(filename, "w") as outfile:
        json.dump(dict, outfile)


def ensure_godot_selfcontained_mode():
    filename = os.path.join(editorDirectory, '._sc_')
    if not os.path.isfile(filename):
        open(filename, 'a').close()


def ensure_godot_editor_project():
    filename = os.path.join(editorDirectory, 'editor_data', 'projects.cfg')
    if not os.path.isfile(filename):
        os.makedirs(os.path.dirname(filename))
        project_root = os.path.abspath(os.path.join(os.path.dirname(
            os.path.realpath(__file__)), '..'))
        with open(filename, "w") as outfile:
            outfile.write("[{project_root}]\n\nfavorite=false\n\n".format(project_root=project_root))
