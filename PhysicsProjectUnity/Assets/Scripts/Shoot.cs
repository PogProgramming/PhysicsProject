using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Shoot : MonoBehaviour
{
    // Make guns into array corresponding to enum int
    //public GameObject[] guns; // 0 pistol, 1 rocket, 2 laser

    public List<GameObject> guns;

    Animator pistolAnimator;
    Animator rocketAnimator;

    public Image normalCrosshair;
    public Image hitCrosshair;

    public GameObject bullet = null;
    public GameObject rocket = null;
    public GameObject orientation = null;
    public GameObject gunEndPoint = null; // To help with rotation of bullet

    public float cooldown = 0.2f;

    [SerializeField] bool canShoot = true;

    public float gunDamage = 0;
    public float gunBulletSpeed = 0;

    // rocket will kill no matter what
    public float rocketForce = 0;
    public float rocketBlastRadius = 0;
    public float blastForce = 0;

    public LayerMask enemyLayer;

    Camera cam = null;

    public enum GunType
    {
        Pistol,
        Rocket
    }

    GunType gunType;

    void Start()
    {
        cam = Camera.main;

        pistolAnimator = guns[(int)GunType.Pistol].GetComponent<Animator>();
        gunType = GunType.Pistol; // default
    }

    // Update is called once per frame
    float timer = 0;

    bool crosshairChange = false;
    float crosshairTimer = 0;
    float crosshairTimeout = 0.1f;
    void Update()
    {
        if (Input.GetMouseButton(0))
            InputShoot();

        if (timer < cooldown)
            timer += Time.deltaTime;
        else
        {
            if (!canShoot) canShoot = true;
        }

        if (crosshairChange)
        {
            crosshairTimer += Time.deltaTime;
            if (crosshairTimer > 0.1f)
            {
                crosshairTimer = 0;
                crosshairChange = false;
                CrosshairHit(false);
            }
        }

        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            if((int)gunType != 0)
                SwitchGun(0);
        }

        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            if ((int)gunType != 1)
                SwitchGun(1);
        }
    }

    void SwitchGun(int gunIndex)
    {
        switch (gunIndex)
        {
            case (int)GunType.Pistol:
            {
                guns[(int)gunType].SetActive(false);
                guns[(int)GunType.Pistol].SetActive(true);

                gunType = GunType.Pistol;


                break;
            }

            case (int)GunType.Rocket:
            {
                guns[(int)gunType].SetActive(false);
                guns[(int)GunType.Rocket].SetActive(true);

                gunType = GunType.Rocket;
                


                break;
            }
        }
    }

    void InputShoot()
    {
        if (canShoot)
        {
            canShoot = false;
            timer = 0;

            switch (gunType)
            {
                case GunType.Pistol:
                {
                    ShootBullet();
                    RunGunShotAnimation();
                    break;
                }

                case GunType.Rocket:
                {
                    ShootRocket();
                    break;
                }
            }
        }
    }

    void RunRocketShotAnimation()
    {
        // vv
    }

    void RunGunShotAnimation()
    {
        pistolAnimator.Play("anim_GunShot", 0, 0f);
        //anim_GunShot
    }

    void CrosshairHit(bool _set)
    {
        if (_set)
        {
            normalCrosshair.enabled = false;
            hitCrosshair.enabled = true;

            crosshairChange = true;
        }
        else
        {
            normalCrosshair.enabled = true;
            hitCrosshair.enabled = false;
        }
    }

    void ShootBullet()
    {
        GameObject bulletObj = Instantiate(bullet, gunEndPoint.transform.position, gunEndPoint.transform.rotation);
        BulletAttack ba = bulletObj.GetComponent<BulletAttack>();
        ba.SetBullet(gunDamage, gunBulletSpeed, cam.transform.forward);

        RaycastHit hit;
        if (Physics.Raycast(gunEndPoint.transform.position, cam.transform.forward, out hit, enemyLayer))
        {
            GameObject mainEnemyBody = hit.transform.gameObject;
            bool checkGood = false;
            while (mainEnemyBody.transform.tag != "Enemy")
            {
                if (mainEnemyBody.transform.parent == null)
                    break;

                mainEnemyBody = mainEnemyBody.transform.parent.gameObject;
                if (mainEnemyBody.transform.tag == "Enemy")
                    checkGood = true;
            }
            if (checkGood)
            {
                CrosshairHit(true);
                mainEnemyBody.transform.GetComponent<EnemyHealth>().TakeDamage(gunDamage, hit.normal, gunBulletSpeed, hit.transform.GetComponent<Rigidbody>());
            }
        }
    }

    void ShootRocket()
    {
        GameObject rocketObj = Instantiate(rocket, gunEndPoint.transform.position, gunEndPoint.transform.rotation);
        RocketAttack rkt = rocketObj.GetComponent<RocketAttack>();

        rkt.SetRocket(cam.transform.forward, rocketForce, blastForce, rocketBlastRadius, enemyLayer);
    }
}
