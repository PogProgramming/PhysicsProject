using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class KillcountUpdateUI : MonoBehaviour
{
    GameSystem gameSystem = null;
    Text killCountText = null;

    public string preText = "Kills remaining: ";

    void Start()
    {
        gameSystem = GameObject.Find("EventSystem").GetComponent<GameSystem>();
        killCountText = GetComponent<Text>();
    }

    // Update is called once per frame
    void Update()
    {
        killCountText.text = preText + gameSystem.GetStringRemainingKills();
    }
}
