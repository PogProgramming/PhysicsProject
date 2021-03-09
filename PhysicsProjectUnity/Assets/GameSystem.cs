using UnityEngine;
using UnityEngine.UI;

public class GameSystem : MonoBehaviour
{
    public bool gameOver = false;

    public int killsRequired = 0;
    public int currentKills = 0;

    public GameObject winnerUI;

    bool spawned = false;

    public RunSpawners rs = null;

    void Start()
    {
    }

    int numberOfSpawners = 7;
    int counterKills = 0;
    bool spawnEnemies = false;

    int lastCurrentKill = 0;

    void Update()
    {
        if (gameOver)
        {
            winnerUI.SetActive(true);
        }

        if(lastCurrentKill != currentKills)
        {
            lastCurrentKill = currentKills;
            counterKills++;
        }

        if(counterKills == numberOfSpawners)
        {
            numberOfSpawners += 7;
            rs.SpawnEnemies();
            spawnEnemies = false;
        }
    }

    public void AdjustKills(int adjustment)
    {
        currentKills += adjustment;

        if(currentKills >= killsRequired)
        {
            gameOver = true;
        }
    }

    public int GetRemainingKills()
    {
        return killsRequired - currentKills;
    }

    public string GetStringRemainingKills()
    {
        return GetRemainingKills().ToString();
    }
}
